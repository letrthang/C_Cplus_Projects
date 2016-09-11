#ifndef COMMON_H_
#define COMMON_H_

// we support maximum 6 color for each CodePeg
typedef enum
{
	NONE_COLOR, // init value
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PINK,
	GREY,
	MAX_COLOR
} PEG_COLOR;

// there is 4 holes respective 4 positions of each CodePeg.
typedef enum
{
	NONE_POSITION, // init value
	FIRST,
	SECOND,
	THIRD,
	FOURTH
} PEG_POSITION;

// value of each KeyPeg
typedef enum
{
	CONTINUE,
	WIN,
	LOSE
} KEY_PEG_RESULT;

#endif /* COMMON_H_ */
