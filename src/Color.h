#pragma once

struct Color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;

	Color () : r(0), g(0), b(0) {}
	Color(Uint8 r, Uint8 g, Uint8 b)
		: r(r), g(g), b(b){}
};

const Color red(255, 0, 0);
const Color green(0, 255, 0);
const Color blue(0, 0, 255);
const Color yellow(255, 255, 0);
const Color cyan(0, 255, 255);
const Color magenta(255, 0, 255);
const Color white(255, 255, 255);
const Color black(0, 0, 0);