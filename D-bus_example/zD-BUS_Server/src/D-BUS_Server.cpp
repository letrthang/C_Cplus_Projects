//============================================================================
// Name        : D-BUS_Server.cpp
// Author      : Thang Le
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/////////////////////////////////////////////////////////////////////////////////////////
// Header files
/////////////////////////////////////////////////////////////////////////////////////////
// Own header

#include "common.h"   // Demo bus defines
#include "server.h"
// System header
#include <gio/gio.h>   // GIO for dbus
#include <glib-2.0/glib.h>   // GLIB for main loop
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Generated headers
#include "example.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Instance init
/////////////////////////////////////////////////////////////////////////////////////////
static GMainLoop         *pLoop     = NULL;
static ThangleExampleInterface *pSkeleton = NULL;
static int callNum = 0;

/////////////////////////////////////////////////////////////////////////////////////////
// Normal functions
/////////////////////////////////////////////////////////////////////////////////////////
 gboolean Emit_My_signal1(gpointer p)
{
    gchar buf[20];

    memset(buf, 0, 20);
    callNum++;
    sprintf(buf, "Server Signal1(%d)", callNum);
    thangle_example_interface_emit_my_signal1(pSkeleton, buf);
    g_print("Emit_My_Signal1() is called.\n");
    return TRUE;
}

 gboolean Emit_My_Signal2(gpointer p)
{
	  callNum++;
	  GVariant *payload = g_variant_new("(is)", callNum, "Server Signal2");
	  thangle_example_interface_emit_my_signal2(pSkeleton, payload);
	  g_print("Emit_My_Signal2() is called.\n");
	  return TRUE;
}


static gboolean My_Method1(ThangleExampleInterface     *object,
                               GDBusMethodInvocation *invocation,
                               const gchar           *in_arg,
                               gpointer               user_data)
{
    g_print("Received method 1 call. Parameter: %s.\n", in_arg);

    //THANGLE_GDBUS_example_set_my_property(pSkeleton, "Server Method...");
    //THANGLE_GDBUS_example_complete_my_method(object, invocation, "Server Method");
    thangle_example_interface_complete_my_method1(object, invocation, in_arg);

    return TRUE;
}


static gboolean My_Method2(ThangleExampleInterface     *object,
                               GDBusMethodInvocation *invocation,
                               GVariant          	 *in_arg,
                               gpointer               user_data)
{
  gint in_arg1 = 0;
  gint in_arg2 = 0;
  gint out_arg2 = 0;
  gchar *out_arg1 = "My Method2 reply";
  GVariant *out_arg = NULL;

  g_print("Received method 2 call.\n");
  // Get the input parameters
  g_variant_get(in_arg, "(ii)", &in_arg1, &in_arg2);

  // Generate the output parameters
  out_arg2 = in_arg1 + in_arg2;
  out_arg = g_variant_new("(si)", out_arg1, out_arg2);

  thangle_example_interface_complete_my_method2(object, invocation, out_arg);

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Callback functions
/////////////////////////////////////////////////////////////////////////////////////////
static void bus_acquired_cb(GDBusConnection *connection,
                                const gchar     *bus_name,
                                gpointer         user_data)
{
    GError *pError = NULL;

    // Second step: Try to get a connection to the given bus.
    pSkeleton = thangle_example_interface_skeleton_new();

    // Third step: Attach to dbus signals
    (void) g_signal_connect(pSkeleton, "handle-my-method1", G_CALLBACK(My_Method1), NULL);
    (void) g_signal_connect(pSkeleton, "handle-my-method2", G_CALLBACK(My_Method2), NULL);

    // Fourth step: Export interface skeleton
    (void) g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(pSkeleton),
                                              connection,
                                              THANGLE_GDBUS_EXAMPLE_OBJECT_PATH,
                                              &pError);

    if(pError != NULL)
    {
         g_print("Error: Failed to export object. Reason: %s.\n", pError->message);
         g_error_free(pError);
         g_main_loop_quit(pLoop);
    }
    else
    {
    	g_print("Bus exported to:  %s.\n", THANGLE_GDBUS_EXAMPLE_OBJECT_PATH);
    }
}

static void name_acquired_cb(GDBusConnection *connection,
                                     const gchar     *bus_name,
                                     gpointer         user_data)
{
    g_print("Acquired bus name: %s.\n", THANGLE_GDBUS_EXAMPLE_BUS_NAME);
}


static void name_lost_cb(GDBusConnection *connection,
                             const gchar     *bus_name,
                             gpointer         user_data)
{
    if(connection == NULL)
    {
        g_print("Error: Failed to connect to dbus.\n");
    }
    else
    {
        g_print("Error: Failed to obtain bus name: %s.\n", THANGLE_GDBUS_EXAMPLE_BUS_NAME);
    }

    g_main_loop_quit(pLoop);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Thread functions
/////////////////////////////////////////////////////////////////////////////////////////
int thread_create()
{
    int err;
    pthread_t thr;

    err = pthread_create(&thr, NULL, run, NULL);

    if (err != 0)
    {
        printf("Can't create thread: %s\n", strerror(err));
    }
    else
    {
        printf("New thread created: %s\n", strerror(err));
    }

    return err;
}

void create()
{
    // Start Dbus communication
    startDBusCommunication();

    // Create new thread
    thread_create();
}

void* run(void * p)
{
    // Start the Main Event Loop which manages all available sources of events
    g_main_loop_run( pLoop );
    return((void *)0);
}

void stop()
{
    // Stop Dbus communication
    stopDBusCommunication();
}

/////////////////////////////////////////////////////////////////////////////////////////
// Dbus communication functions
/////////////////////////////////////////////////////////////////////////////////////////
int startDBusCommunication()
{
    int bRet = TRUE;

    // Init for usage of "g" types
    g_type_init();

    g_print("startDBusCommunication: Server started.\n");

    // Create main loop, but do not start it.
    pLoop = g_main_loop_new(NULL, FALSE);

    // First step: Connect to dbus
    (void) g_bus_own_name(THANGLE_GDBUS_EXAMPLE_BUS,
                        THANGLE_GDBUS_EXAMPLE_BUS_NAME,
                        G_BUS_NAME_OWNER_FLAGS_NONE,
                        &bus_acquired_cb,
                        &name_acquired_cb,
                        &name_lost_cb,
                        NULL,
                        NULL);

    // Emit my signal1 every 3 second to trigger example communication
    g_timeout_add_seconds(3, &Emit_My_signal1, NULL);

    // Emit my signal2 every 4 second to trigger example communication
    g_timeout_add_seconds(4, &Emit_My_Signal2, NULL);

    return (bRet);
}

int stopDBusCommunication()
{
    int bRet = FALSE;

    if (pLoop != 0)
    {
        g_main_loop_quit(pLoop);
        g_main_loop_unref(pLoop);
        bRet = TRUE;
    }

    return (bRet);
}

int main()
{
	create();
	g_main_loop_run( pLoop );
}


