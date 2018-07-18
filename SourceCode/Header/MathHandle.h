#pragma once
class MathHandle {
public :
	float static LerpFloat(float start, float end, float lerp) {
		return (start + (end - start)*lerp);
	}
	int static LerpInt(int start, int end, float lerp) {
		return (int)(start + (end - start)*lerp);
	}
	double static LerpDouble(double start, double end, float lerp) {
		return start + (end - start)*lerp;
	}
	float static ClampFloat(float min, float max, float spe) {
		return spe > max ? max : spe < min ? min : spe;
	}
	float static AbsFloat(float a) {
		return a < 0 ? -a : a;
	}
};