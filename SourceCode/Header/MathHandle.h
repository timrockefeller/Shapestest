#pragma once
class MathHandle {
public :
	float static LerpFloat(float start, float end, float lerp) {
		return start - (start - end)*lerp;
	}
	int static LerpInt(int start, int end, float lerp) {
		return start - (int)((start - end)*lerp);
	}
	double static LerpDouble(double start, double end, float lerp) {
		return start - (start - end)*lerp;
	}
	float static ClampFloat(float min, float max, float spe) {
		return spe > max ? max : spe < min ? min : spe;
	}
	int static ClampInt(int min, int max, int spe) {
		return spe > max ? max : spe < min ? min : spe;
	}
	int static MinInt(int first, int second) {
		return first > second ? second : first;
	}
	float static AbsFloat(float a) {
		return a < 0 ? -a : a;
	}
};