#pragma once

#include <chrono>

namespace Rune
{
    class Time
    {
    private:
        friend class Application;
        std::chrono::time_point<std::chrono::high_resolution_clock> _start;
        float _currentTime;
                
        void Update() 
        {
            _currentTime = Elapsed();
        }

    public:
        Time() { Reset(); }

        void Reset()
		{
			_start = std::chrono::high_resolution_clock::now();
            _currentTime = 0;
		}

		float Elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _start).count() * 0.001f * 0.001f * 0.001f;
		}

		float ElapsedMillis()
		{
			return Elapsed() * 1000.0f;
		}

        float DeltaTime() 
        {
            return Elapsed() - _currentTime;
        }

        float DeltaTimeMillis()
        {
            return ElapsedMillis() - (_currentTime*1000.0f);
        }

        float CurrentFPS()
        {
            return 1.0f/DeltaTime();
        }
    };
}