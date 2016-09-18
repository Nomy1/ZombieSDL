#include "Timing.h"
#include <SDL/SDL.h>

namespace TE
{
	FPSLimiter::FPSLimiter()
	{
	}
	FPSLimiter::~FPSLimiter()
	{
	}

	void FPSLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::setMaxFPS(float maxFPS)
	{
		m_maxFPS = maxFPS;
	}

	void FPSLimiter::frameBegin()
	{
		m_startTick = SDL_GetTicks();
	}

	void FPSLimiter::frameEnd()
	{
		calcFPS();
		limitFPS();
	}

	float FPSLimiter::getFPS()
	{
		return m_currFPS;
	}

	void FPSLimiter::calcFPS()
	{
		static const int FPS_SAMPLE_NUM = 10;
		static Uint32 frameTimes[FPS_SAMPLE_NUM];
		static int frameSampleIndex = 0;
		static Uint32 prevTick = SDL_GetTicks();

		// Set previous frame difference
		Uint32 currTick = SDL_GetTicks();
		frameTimes[frameSampleIndex++ % FPS_SAMPLE_NUM] = currTick - prevTick;
		prevTick = currTick;

		// Calculate calculable frame count
		int count;
		if (frameSampleIndex < FPS_SAMPLE_NUM)
		{
			count = frameSampleIndex;
		}
		else
		{
			count = FPS_SAMPLE_NUM;
		}

		// Average all sample frames
		float avgFps = 0.0f;
		for (int i = 0; i < count; i++)
		{
			avgFps += frameTimes[i];
		}

		avgFps /= count;

		if (avgFps > 0.0f)
		{
			m_currFPS = 1000.0f / avgFps;
		}
		else
		{
			m_currFPS = 60.0f;
		}
	}

	void FPSLimiter::limitFPS()
	{
		// Keep display refreshed to a max FPS
		Uint32 loopEndTick = SDL_GetTicks();
		Uint32 loopTickDiff = loopEndTick - m_startTick;
		if (1000.0f / m_maxFPS > loopTickDiff)
		{
			SDL_Delay(1000 / m_maxFPS - loopTickDiff);
		}
	}
}
