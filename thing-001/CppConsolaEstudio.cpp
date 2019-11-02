//////////////////////////////////////////////////
// By @BrainCodec 
// Date: 2 November, 2019
// Testing limits, cfloat headers
// Testing function/lambda as a function parameter

#include <iostream>
#include <limits>
#include <cfloat>
#include <vector>
#include <assert.h>

// #define _DEBUG_FUNCTION_ON_CONSTRUCTION
// #define _SHOWING_MAX_VALUES
// #define _FUNC01_PLOT
#define _FUNC02_PLOT

namespace BrainCodec
{
	namespace PlotterManager
	{
		enum class PlotterType {VERBOSED, REDUCED};

		template <typename T>
		class FuncPlotter
		{
			typedef T fcnType(T);

			typedef struct _vector2D
			{
				T x;
				T y;
			} Vector2D;

		public:
			FuncPlotter(fcnType fcn, T x0, T incr, uint32_t n, 
				PlotterType type = PlotterType::VERBOSED)
			{
				assert(fcn != nullptr);

				m_Type = type;
				m_Fcn = fcn;

				for (uint32_t i = 0; i < n; i++)
				{
#ifdef _DEBUG_FUNCTION_ON_CONSTRUCTION
					std::cout << " x :" << x0 << "   f(x) : " <<
						static_cast<fcnType*>(m_Fcn)(x0) << "\n";
#endif
					m_Values.push_back({ x0, fcn(x0) });
					x0 += incr;
				}
			}

			void Plot()
			{
				for (auto v : m_Values)
				{
					if (m_Type == PlotterType::VERBOSED)
					{
						std::cout << " x :" << v.x << "   f(x) : " << v.y << "\n";
					}
					else
					{
						std::cout << v.x << ", " << v.y << "\n";
					}
				}
			}

			void IntervalPlotByIndex(uint32_t start, uint32_t count)
			{
				assert(start >= 0 && start < m_Values.size());
				assert(count > 0 && count < m_Values.size());

				for (uint32_t i = 0; i < count; i++)
				{
					if (m_Type == PlotterType::VERBOSED)
					{
						std::cout << " x :" << m_Values[start + i].x << "   f(x) : " <<
							m_Values[start + i].y << "\n";
					}
					else
					{
						std::cout << m_Values[start + i].x << ", " <<
							m_Values[start + i].y << "\n";
					}
				}
			}

			T Value(T x)
			{
				assert(m_Fcn != nullptr);

				return static_cast<fcnType*>(m_Fcn)(x);
			}

		private:
			std::vector<Vector2D> m_Values;
			PlotterType m_Type;
			void* m_Fcn;
		};
	}
}


int main()
{
#ifdef _SHOWING_MAX_VALUES
	std::cout << "uint8_t max : " << std::numeric_limits<uint8_t>().max() << "\n";
	std::cout << "uint16_t max : " << std::numeric_limits<uint16_t>().max() << "\n";
	std::cout << "uint32_t max : " << std::numeric_limits<uint32_t>().max() << "\n";
	std::cout << "uint64_t max : " << std::numeric_limits<uint64_t>().max() << "\n";
	std::cout << "float max : " << FLT_MAX << "\n";
	std::cout << "double max : " << DBL_MAX << "\n";
#endif

#ifdef _FUNC01_PLOT
	// Plotting a simple function
	auto f = BrainCodec::PlotterManager::FuncPlotter<double>(
		[](double x) -> double
	{
		return x * x + 1.0 / x;
	}, 0.01, 0.01, 10);

	f.Plot();
#endif

#ifdef _FUNC02_PLOT
	// Plotting a function using 'integer values'
	auto fXSquared = BrainCodec::PlotterManager::FuncPlotter<int>(
		[](int x) -> int
	{
		return x * x;
	}, 0, 1, 10, BrainCodec::PlotterManager::PlotterType::REDUCED);

	fXSquared.Plot();
	auto singleValue = fXSquared.Value(100);
	fXSquared.IntervalPlotByIndex(5, 5);
#endif
}