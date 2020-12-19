/**
 * @file pbm_file.hpp
 * @brief C++ program that holds vec2D, vec3D, vec4D objects
 * @author Ari Nguyen
 */

template <typename T>
class _vec2 {
    public:
        T x, y;
    public: 
        _vec2() = default;
        _vec2(T x, T y) 
            : x(x), y(y) 
        {}

        template <typename T2>
	    explicit operator _vec2<T2>() const {
		    return {(T2)x, (T2)y};
        }

        T lenSqrt() const {
            ;
        }
        T len() const {
            return sqrt(lenSqrt());
        }
        _vec2& normalize() {
            const T length = len();
            x /= length;
            y /= length;
            return *this;
        }
        _vec2 getNormalized() const {
            _vec2 norm = *this;
            norm.normalize();
            return norm;
        }

        _vec2 operator-() const {
            return _vec2(-x, -y);
        }
        _vec2& operator=(const _vec2 &rhs) const {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
        bool operator==(const _vec2 &rhs) {
            return x == rhs.x && y == rhs.y;
        }
        bool operator!=(const _vec2 &rhs) { 
            return !(*this == rhs);
        }

        _vec2& operator-=(const _vec2 &rhs) {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        _vec2& operator+=(const _vec2 &rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        _vec2& operator/=(const T &rhs) {
            x /= rhs;
            y /= rhs;
            return *this;
        }
        _vec2& operator*=(const T &rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }
        
        _vec2 operator-(const _vec2 &rhs) const {
            return _vec2(*this) -= rhs;
        }
        _vec2 operator+(const _vec2 &rhs) const {
            return _vec2(*this) += rhs;
        }
        _vec2 operator/(const T &rhs) const {
            return _vec2(*this) /= rhs;
        }
        _vec2 operator*(const T &rhs) const {
            return _vec2(*this) *= rhs;
        }
        // scalar product: u.v = u1v1 + u2v2
        T operator*(const _vec2 &rhs) const {
            return _vec2(*this) *= rhs;
        }
};  

template <typename T>
class _vec3 : public _vec2<T> {
    public:
        T z;
    public:
        _vec3() = default;
        _vec3(T x, T y, T z) 
            : _vec2(x, y), z(z) 
        {}

        template <typename T2>
	    explicit operator _vec3<T2>() const {
		    return {(T2)x, (T2)y, (T2)z};
        }

        T lenSqrt() const {
            ;
        }
        T len() const {
            return sqrt(lenSqrt());
        }
        _vec3& normalize() {
            const T length = len();
            x /= length;
            y /= length;
            z /= length;
            return *this;
        }
        _vec3 getNormalized() const {
            _vec3 norm = *this;
            norm.normalize();
            return norm;
        }

        _vec3 operator-() const {
            return _vec3(-x, -y, -z);
        }
        _vec3& operator=(const _vec3 &rhs) const {
            x = rhs.x;
            y = rhs.y;
            y = rhs.z;
            return *this;
        }
        bool operator==(const _vec3 &rhs) {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }
        bool operator!=(const _vec3 &rhs) { 
            return !(*this == rhs);
        }

        _vec3& operator-=(const _vec3 &rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        _vec3& operator+=(const _vec3 &rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        _vec3& operator/=(const T &rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }
        _vec3& operator*=(const T &rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        
        _vec3 operator-(const _vec3 &rhs) const {
            return _vec3(*this) -= rhs;
        }
        _vec3 operator+(const _vec3 &rhs) const {
            return _vec3(*this) += rhs;
        }
        _vec3 operator/(const T &rhs) const {
            return _vec3(*this) /= rhs;
        }
        _vec3 operator*(const T &rhs) const {
            return _vec3(*this) *= rhs;
        }
        // scalar product: u.v = u1v1 + u2v2
        T operator*(const _vec3 &rhs) const {
            return _vec3(*this) *= rhs;
        }
};

template <typename T> 
class _vec4 : public _vec3<T> {
    public:
        T w;
    public:
        _vec4() = default;
        _vec4(T x, T y, T z) 
            : _vec3(x, y), z(z) 
        {}

        template <typename T2>
	    explicit operator _vec4<T2>() const {
		    return {(T2)x, (T2)y, (T2)z};
        }

        T lenSqrt() const {
            ;
        }
        T len() const {
            return sqrt(lenSqrt());
        }
        _vec4& normalize() {
            const T length = len();
            x /= length;
            y /= length;
            z /= length;
            return *this;
        }
        _vec4 getNormalized() const {
            _vec4 norm = *this;
            norm.normalize();
            return norm;
        }

        _vec4 operator-() const {
            return _vec4(-x, -y, -z);
        }
        _vec4& operator=(const _vec4 &rhs) const {
            x = rhs.x;
            y = rhs.y;
            y = rhs.z;
            return *this;
        }
        bool operator==(const _vec4 &rhs) {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }
        bool operator!=(const _vec4 &rhs) { 
            return !(*this == rhs);
        }

        _vec4& operator-=(const _vec4 &rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        _vec4& operator+=(const _vec4 &rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        _vec4& operator/=(const T &rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }
        _vec4& operator*=(const T &rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        
        _vec4 operator-(const _vec4 &rhs) const {
            return _vec4(*this) -= rhs;
        }
        _vec4 operator+(const _vec4 &rhs) const {
            return _vec4(*this) += rhs;
        }
        _vec4 operator/(const T &rhs) const {
            return _vec4(*this) /= rhs;
        }
        _vec4 operator*(const T &rhs) const {
            return _vec4(*this) *= rhs;
        }
        // scalar product: u.v = u1v1 + u2v2
        T operator*(const _vec4 &rhs) const {
            return _vec4(*this) *= rhs;
        }
};

typedef _vec2<int> vec2i;
typedef _vec2<double> vec2d;
typedef _vec2<float> vec2f;

typedef _vec3<int> vec3i;
typedef _vec3<double> vec3d;
typedef _vec3<float> vec3f;

typedef _vec4<int> vec4i;
typedef _vec4<double> vec4d;
typedef _vec4<float> vec4f;

