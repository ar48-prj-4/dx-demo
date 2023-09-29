#pragma once
#include "CommonInclude.h"
#include "YamYamEngine.h"

using namespace ya::math;

namespace ya
{
	enum class KEY_CODE
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		//Special Key
		ENTER, ESC, LSHIFT, LALT, LCTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		LBTN, RBTN,

		//Num Pad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		//Num Line
		N_0, N_1, N_2, N_3, N_4, N_5,
		N_6, N_7, N_8, N_9,

		END,
	};
	enum KEY_STATE
	{
		DOWN,
		PRESSED,
		UP,
		NONE,
	};

	class Input
	{
	public:
		struct Key
		{
			KEY_CODE  eType;
			KEY_STATE eState;
			bool	  bPressed;
		};

		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(KEY_CODE code)					// inline : 최적화 옵션, 자주 사용되는 것들은 인라인 사용하는게 좋음
		{																	// _forceinline : inline을 무조건(판단없이)
			return mKeys[(int)code].eState == KEY_STATE::DOWN;				// inline은 헤더에서만 사용 가능
		}
		__forceinline static bool GetKeyUp(KEY_CODE code)
		{
			return mKeys[(int)code].eState == KEY_STATE::UP;
		}
		__forceinline static bool GetKey(KEY_CODE code)
		{
			return mKeys[(int)code].eState == KEY_STATE::PRESSED;				// 같으면 true 반환, 다르면 false 반환
		}

		static __forceinline KEY_STATE GetKeyState(KEY_CODE keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eState;
		}

		static __forceinline Vector2 GetMousPosition()
		{
			return mMousPosition;
		}

	private:
		Input() = delete;
		~Input() = delete;

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousPosition;
	};
}

