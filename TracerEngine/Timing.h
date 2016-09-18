#pragma once

namespace TE
{
	class FPSLimiter
	{
	public:
		FPSLimiter();
		~FPSLimiter();

		void init(float maxFPS);
		void setMaxFPS(float maxFPS);
		void frameBegin();
		void frameEnd();
		float getFPS();
	private:
		void calcFPS();
		void limitFPS();
		float m_maxFPS;
		float m_currFPS;
		unsigned int m_startTick;
	};
}