/////////////////////////////////////////////////////////////////////////////////////////
// Header files
/////////////////////////////////////////////////////////////////////////////////////////
// Own header
#include "common.h"   // Demo bus defines
#include "client.h" 

// System header
#include <gio/gio.h>   // GIO for dbus
#include <glib-2.0/glib.h>   // GLIB for main loop
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// Generated headers
#include "example.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Instance init
/////////////////////////////////////////////////////////////////////////////////////////
static GMainLoop         *pLoop       = NULL;
static GDBusConnection   *pConnection = NULL;
static ThangleExampleInterface *pProxcy     = NULL;

static METHOD_CALLBACK_T g_method_callback;
static SIGNAL_CALLBACK_T g_signal_callback;

/////////////////////////////////////////////////////////////////////////////////////////
// sync method call
/////////////////////////////////////////////////////////////////////////////////////////
void My_method_1(const gchar * in_arg, gchar** out_arg, GError** pError)
{
    //g_print("My_method_1: Property retrieved. Value: %s.\n", THANGLE_GDBUS_example_get_my_property(pProxcy));

    // Call the server's dbus methods
    thangle_example_interface_call_my_method1_sync(pProxcy, in_arg, out_arg, NULL, pError);

    #if 1
    if(pError == NULL)
    {
        g_print("My_method_1: Method called. Return value: %s.\n", out_arg);
        g_free(out_arg);
    }
    else
    {
        //g_print("My_method_1: Failed to call method. Reason: %s.\n", pError->message);
        //g_error_free(pError);
    }
#endif
    return;
}

// Async method callback
static void Method1Callback(GObject* source_object, GAsyncResult* res, gpointer user_data)
{
  gchar *out_arg = NULL;
  GError *pError = NULL;

  thangle_example_interface_call_my_method1_finish(pProxcy, &out_arg, res, &pError);

  if (pError == NULL)
  {
	g_print("Method1Callback = %s.\n", out_arg);
    if(g_method_callback.callback1 != NULL)
    {
      g_method_callback.callback1(out_arg, false);
      g_free(out_arg);
    }
  }
  else
  {
    g_method_callback.callback1(out_arg, true);
    g_print("Method1Callback: error message: %s.\n", pError->message);
    g_error_free(pError);
  }

}

void My_method_1_Async(const gchar * in_arg)
{
  thangle_example_interface_call_my_method1(pProxcy, in_arg, NULL, Method1Callback, NULL);
  return;
}

//Sync call
void My_method_2(const gint in_arg1, const gint in_arg2, gchar **out_arg1, gint *out_arg2, GError** pError)
{
  GVariant *in_arg = NULL;
  GVariant *out_arg = NULL;
  GError *Error = NULL;
  
  // Generate the input parameters
  in_arg = g_variant_new("(ii)", in_arg1, in_arg2);
  // Call the server's dbus methods
  thangle_example_interface_call_my_method2_sync(pProxcy, in_arg, &out_arg, NULL, pError);
  if (*pError == NULL)
  {
    // Get the result from the output parameter
    g_variant_get(out_arg, "(si)", out_arg1, out_arg2);
  }
  return;
}

//Async callback
static void Method2Callback(GObject* source_object, GAsyncResult* res, gpointer user_data)
{
  GVariant *out_arg = NULL;
  GError *pError = NULL;
  gint out_arg2 = 0;
  gchar *out_arg1 = NULL;
  
  thangle_example_interface_call_my_method2_finish(pProxcy, &out_arg, res, &pError);
  if (pError == NULL)
  {
    // Get the result from the output parameter
    g_variant_get(out_arg, "(si)", &out_arg1, &out_arg2);
    if (g_method_callback.callback2 != NULL)
    {
      g_method_callback.callback2(out_arg1, out_arg2, false);
      g_free(out_arg1);
    }
  }
  else
  {
    g_method_callback.callback2(out_arg1, out_arg2, true);
    g_error_free(pError);
  }
}

// Async call
void My_method_2_Async(const gint in_arg1, const gint in_arg2)
{
  GVariant *in_arg = g_variant_new("(ii)", in_arg1, in_arg2);
  thangle_example_interface_call_my_method2(pProxcy, in_arg, NULL, Method2Callback, NULL);
  return;
}

void registerSignalCallback(SIGNAL_CALLBACK_T *callback)
{
  if (callback != NULL)
  {
    memcpy(&g_signal_callback, callback, sizeof(SIGNAL_CALLBACK_T));
  }
  else
  {
    g_print("registerSignalCallback: parameter point is NULL");
  }
}

void registerMethodCallback(METHOD_CALLBACK_T *callback)
{
  if (callback != NULL)
  {
    memcpy(&g_method_callback, callback, sizeof(METHOD_CALLBACK_T));
  }
  else
  {
    g_print("registerMethodCallback: parameter point is NULL");
  }
}

static gboolean My_Signal_1_Handler(ThangleExampleInterface *object,
                                          const gchar       *arg,
                                          gpointer          user_data)
{
	 gchar** out_arg;
	 GError** pError;

    g_print("My_Signal_1_Handler: Signal received. Paramater value: %s.\n", arg);

    // callback function
    if (g_signal_callback.callback1 != NULL)
    {
      g_signal_callback.callback1(arg);
    }
    My_method_1_Async(arg);
	
    return TRUE;
}

static gboolean My_Signal_2_Handler(ThangleExampleInterface *object,
                                          GVariant       *arg,
                                          gpointer          user_data)
{


  // Get the value from GVariant
  gint int_arg =  0;
  gchar *char_arg = 0;
  g_variant_get(arg, "(is)", &int_arg, char_arg);
  
  g_print("My_Signal_2_Handler: Signal received. Paramater value: %d.\n", int_arg);

  // callback function
  if (g_signal_callback.callback2 != NULL)
  {
    g_signal_callback.callback2(int_arg, char_arg);
  }
  g_free(char_arg);
  return TRUE;
}

void dbusClientConnectMySignal_1( ThangleExampleInterface* bus_proxy, GDBusConnection* bus_connection)
{
    (void) g_signal_connect(bus_proxy, "my-signal1", G_CALLBACK(My_Signal_1_Handler), NULL);

    //g_timeout_add(1000, &My_method_1, NULL);
}

void dbusClientConnectMySignal_2( ThangleExampleInterface* bus_proxy, GDBusConnection* bus_connection)
{
    (void) g_signal_connect(bus_proxy, "my-signal2", G_CALLBACK(My_Signal_2_Handler), NULL);

    //g_timeout_add(1000, &My_method_1, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Thread functions
/////////////////////////////////////////////////////////////////////////////////////////

void *run(void *arg)
{
    // Start the Main Event Loop which manages all available sources of events
    g_main_loop_run( pLoop );
	
    return((void *)0);
}

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

bool initialize()
{
    if (pProxcy == NULL)
    {
       // Start Dbus communication
       startDBusCommunication();

       // Create new thread
       thread_create();
       return true;
    }
    else
    {
       g_print("initialize: Already initialized.\n");
       return false;
    }
}



void uninitialize()
{
    // Stop Dbus communication
    stopDBusCommunication();
    pProxcy = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Dbus communication functions
/////////////////////////////////////////////////////////////////////////////////////////
int startDBusCommunication()
{
    int     iLoop      = 0;
    int     bRet       = TRUE;
    GError *pConnError = NULL;
    GError *pProxError = NULL;

    // Init for usage of "g" types
    g_type_init();

    g_print("startDBusCommunication: Client started.\n");

    do
    {
        bRet = TRUE;
        ++iLoop;
        g_print("StartDBusCommunication: try %d.\n", iLoop);

        // Create main loop, but do not start it.
        pLoop = g_main_loop_new(NULL, FALSE);

        // First step: Connect to dbus        
        pConnection = g_bus_get_sync(THANGLE_GDBUS_EXAMPLE_BUS, NULL, &pConnError);

        if(pConnError == NULL)
        {
            // Second step: Try to get a connection to the given bus.
            pProxcy = thangle_example_interface_proxy_new_sync(pConnection,
                                                   G_DBUS_PROXY_FLAGS_NONE,
                                                   THANGLE_GDBUS_EXAMPLE_BUS_NAME,
                                                   THANGLE_GDBUS_EXAMPLE_OBJECT_PATH,
                                                   NULL,
                                                   &pProxError);
            if (pProxcy == 0)
            {
                g_print("StartDBusCommunication: Failed to create proxy. Reason: %s.\n", pProxError->message);
                g_error_free(pProxError);
                bRet = FALSE;
            }
        }
        else
        {
            g_print("StartDBusCommunication: Failed to connect to dbus. Reason: %s.\n", pConnError->message);
            g_error_free(pConnError);
            bRet = FALSE;
        }

        if ( bRet == FALSE )
        {
          //wait 250 millisecs
          usleep( 250*1000 );
        }
    }
    while( bRet == FALSE );

    if( bRet == TRUE)
    {
        // Third step: Attach to dbus signals
        dbusClientConnectMySignal_1( pProxcy, pConnection );
        dbusClientConnectMySignal_2( pProxcy, pConnection );
    }

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
	initialize();
	g_main_loop_run( pLoop );
}

