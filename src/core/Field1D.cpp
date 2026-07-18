#include "core/Field1D.h"

/* Constructor */
Field1D::Field1D(const Grid1D& grid, std::size_t num_variables) : grid_(grid), values_(grid.size(), Vector(num_variables)){}

/* Capacity */
std::size_t Field1D::size() const noexcept {
	return values_.size();
}

std::size_t Field1D::numVariables() const noexcept {
	if (values_.empty()) return 0;

	return values_.front().size();
}

/* Element access */
Vector& Field1D::operator[](std::size_t i) {
	return values_[i];
}

Vector& Field1D::at(std::size_t i) {
	return values_.at(i);
}

const Vector& Field1D::at(std::size_t i) const {
	return values_.at(i);
}

/* Utilities */
void Field1D::fill(double value) {
	for (auto& cell : values_){
		cell.fill(value);
	}
}

/* Access */
const Grid1D& Field1D::grid() const {
	return grid_;
}



