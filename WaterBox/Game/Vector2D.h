#pragma once


template <typename T>
class Vector2D
{
public:
	Vector2D(size_t sizX, size_t sizY) :SizeX(sizX), SizeY(sizY), Field(sizX* sizY)
	{}
	Vector2D() = default;

	inline T& Get(size_t x, size_t y) {
		if (x >= SizeX || y >= SizeY)
			throw std::out_of_range("Index out of bounds");

		return Field[x + y * SizeX];
	}

	inline T& operator()(size_t x, size_t y) noexcept {
		return Field[x + y * SizeX];
	}

	const inline T& operator()(size_t x, size_t y) const noexcept {
		return Field[x + y * SizeX];
	}

	void resize(size_t sizX, size_t sizY) {
		SizeX = sizX;
		SizeY = sizY;
		Field.resize(sizX * sizY);
	}

	const inline std::vector <T>& GetVector()	const {
		return Field;
	}
	inline std::vector <T>& GetVector() {
		return Field;
	}
private:
	size_t SizeX = -1, SizeY = -1;
	std::vector <T> Field;
};