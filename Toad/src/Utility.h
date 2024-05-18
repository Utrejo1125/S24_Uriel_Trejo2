#pragma once

#define START_GAME(className) \
int main()\
{\
	className _game;\
	_game.Run();\
	return 0;\
}

#ifdef TOAD_MS_COMPILER
	#ifdef TOAD_LIB
		#define	TOAD_API __declspec(dllexport)
	#else
		#define	TOAD_API __declspec(dllimport)
	#endif
#else
		#define TOAD_API
#endif


#if TOAD_DEBUG==2
	#define TOAD_ERROR(x) std::cout<<x<<std::endl;
	#define TOAD_LOG(x) std::cout<<x<<std::endl;
#elif TOAD_DEBUG==1
	#define TOAD_ERROR(x) std::cout<<x<<std::endl;
	#define TOAD_LOG(x)
#else
	#define TOAD_ERROR(x)
	#define TOAD_LOG(x)
#endif