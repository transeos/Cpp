// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 24/8/22.
//
//*****************************************************************

#include <iostream>

namespace 🔮 = std;

using 🔢 = int;
using 💀 = void;
using 🤞 = bool;

#define 👂 auto
#define 👍 true
#define 👎 false

#define 🖥 🔮::cout
#define 🔽 🔮::endl
#define 🕜 🔮::time
#define 🔙 return

#define 🤗 "Hello"
#define 😏 "Hi"
#define 🌍 " World!!!"

🔢 main()
{
    👂 😈 = []() -> 🤞 { 🔙 🕜(0) % 2; };
    🖥 << (😈() == 👍 ? 🤗 : 😏) << 🌍 << 🔽;
    🔙 0;
}