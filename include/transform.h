struct Position {
	double x;
	double y;
	Position(double x = 0.0f, double y = 0.0f)
		: x(x), y(y)
	{
	}

	//Assignment operators
	Position& operator=(const Position& a) {
		x = a.x;
		y = a.y;
		return *this;
	}

	//Addition operators
	Position operator+(const Position& a) const {
		return Position(a.x + x, a.y + y);
	}

	Position& operator+=(const Position& a) {
		x = a.x + x;
		y = a.y + y;
		return *this;
	}

	//Subtraction operators
	Position operator-(const Position& a) const {
		return Position(x - a.x, y - a.y);
	}

	Position& operator-=(const Position& a) {
		x = x - a.x;
		y = y - a.y;
		return *this;
	}

};

struct Size {
	double x;
	double y;
	Size(double x = 1.0f, double y = 1.0f)
		: x(x), y(y)
	{
	}

	//Assignment operators
	Size& operator=(const Size& a) {
		x = a.x;
		y = a.y;
		return *this;
	}

	//Addition operators
	Size operator+(const Size& a) const {
		return Size(a.x + x, a.y + y);
	}

	Size& operator+=(const Size& a) {
		x = a.x + x;
		y = a.y + y;
		return *this;
	}

	//Subtraction operators
	Size operator-(const Size& a) const {
		return Size(x - a.x, y - a.y);
	}

	Size& operator-=(const Size& a) {
		x = x - a.x;
		y = y - a.y;
		return *this;
	}
};

struct Rotation {
	double degrees;
	Rotation(double deg = 0.0f)
		: degrees(deg)
	{
	}

	//Assignment operators
	Rotation& operator=(const Rotation& a) {
		degrees = a.degrees;
		return *this;
	}

	//Addition operators
	Rotation operator+(const Rotation& a) const {
		return Rotation(degrees + a.degrees);
	}

	Rotation& operator+=(const Rotation a) {
		degrees = a.degrees + degrees;
		return *this;
	}

	//Subtraction operators
	Rotation operator-(const Rotation& a) const {
		return Rotation(degrees - a.degrees);
	}

	Rotation& operator-=(const Rotation a) {
		degrees = degrees - a.degrees;
		return *this;
	}
};

struct Transform {
	Position pos;
	Rotation rot;
	Size size;
	Transform(Position pos = Position(), Size size = Size(), Rotation rot = Rotation())
		: pos(pos), size(size), rot(rot)
	{
	}

	//Assignment operators
	Transform& operator=(const Transform a) {
		pos = a.pos;
		rot = a.rot;
		size = a.size;
		return *this;
	}

	//Addition operators
	Transform operator+(const Transform a) const {
		return Transform(pos + a.pos, size + a.size, rot + a.rot);
	}

	Transform& operator+=(const Transform a) {
		pos = pos + a.pos;
		size = size + a.size;
		rot = rot + a.rot;
	}

	//Subtraction operators
	Transform operator-(const Transform a) const {
		return Transform(pos + a.pos, size + a.size, rot + a.rot);
	}

	Transform& operator-=(const Transform a) {
		pos = pos - a.pos;
		size = size - a.size;
		rot = rot - a.rot;
	}
};