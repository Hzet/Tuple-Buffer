#include <iostream>

#include "tuple-buffer.hpp"

#define PRINT(x) std::cout << #x << " = " << x << std::endl;

template <std::size_t I = 0u, class... Args>
void print(const haz::CTupleBuffer<Args...> &ub, std::size_t index)
{
	std::cout << ub.get<I>(index);

	if constexpr (I + 1u < sizeof...(Args))
	{
		std::cout << ", ";
		print<I + 1u>(ub, index);
	}
	else
		std::cout << std::endl;
}

template <class... Args>
void print(const haz::CTupleBuffer<Args...> &ub)
{
	const std::size_t size = ub.getCount();
	for (std::size_t i = 0u; i < size; i++)
		print(ub, i);
}
int main()
{
	haz::CTupleBuffer<std::uint32_t, std::uint64_t, std::uint8_t> u32_64_8;
	haz::CTupleBuffer<std::uint16_t, std::uint16_t, std::uint8_t> u16_16_8;
	haz::CTupleBuffer<std::uint64_t, std::uint64_t, std::uint64_t> u64_64_64;

	PRINT(u32_64_8.getCount());
	PRINT(u16_16_8.getCount());
	PRINT(u64_64_64.getCount());
	PRINT(u32_64_8.getStrideSize());
	PRINT(u16_16_8.getStrideSize());
	PRINT(u64_64_64.getStrideSize());

	u32_64_8.push_back(0xFFFFFFFF, 0xFFFF, 0xF);
	u16_16_8.push_back(0xFFFFFF, 0xFF, 0xF);
	u64_64_64.push_back(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);

	print(u32_64_8);
	print(u16_16_8);
	print(u64_64_64);
}