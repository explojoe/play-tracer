#include "mat44.hpp"
#include "catch.hpp"
#include "vec3.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdint.h>

// identity
Mat44::Mat44() {
    memset(data, 0, sizeof(data));
    for (uint32_t i = 0; i < 4; i++) {
        data[i * 4 + i] = 1;
    }
}

Mat44::Mat44(float data2[16]) { memcpy(data, data2, sizeof(data)); }

Mat44 Mat44::scale(Vec3 translateBy) {
    Mat44 mat;
    mat.data[0] = translateBy.x;
    mat.data[5] = translateBy.y;
    mat.data[10] = translateBy.z;
    return mat;
}

Mat44 Mat44::rotatePitch(float pitch) {
    float cosA = cos(pitch);
    float sinA = sin(pitch);
    Mat44 mat;
    mat.data[0] = cosA;
    mat.data[2] = sinA;
    mat.data[8] = -sinA;
    mat.data[10] = cosA;
    return mat;
}

Mat44 Mat44::rotateYaw(float yaw) {
    float cosA = cos(yaw);
    float sinA = sin(yaw);
    Mat44 mat;
    mat.data[0] = cosA;
    mat.data[1] = -sinA;
    mat.data[4] = sinA;
    mat.data[5] = cosA;
    return mat;
}

Mat44 Mat44::rotateRoll(float roll) {
    float cosA = cos(roll);
    float sinA = sin(roll);
    Mat44 mat;
    mat.data[5] = cosA;
    mat.data[6] = -sinA;
    mat.data[9] = sinA;
    mat.data[10] = cosA;
    return mat;
}

Mat44 Mat44::rotate(float angle, Vec3 axis) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    Mat44 mat;
    mat.data[0] = cosA + axis.x * axis.x * (1 - cosA);
    mat.data[1] = axis.x * axis.y * (1 - cosA) - axis.z * sinA;
    mat.data[2] = axis.x * axis.z * (1 - cosA) + axis.y * sinA;
    mat.data[4] = axis.y * axis.x * (1 - cosA) + axis.z * sinA;
    mat.data[5] = cosA + axis.y * axis.y * (1 - cosA);
    mat.data[6] = axis.y * axis.z * (1 - cosA) - axis.x * sinA;
    mat.data[8] = axis.z * axis.x * (1 - cosA) - axis.y * sinA;
    mat.data[9] = axis.z * axis.y * (1 - cosA) + axis.x * sinA;
    mat.data[10] = cosA + axis.z * axis.z * (1 - cosA);
    return mat;
}

Mat44 Mat44::operator*(Mat44 other) const {
    Mat44 mat;
    float total;
    for (uint32_t a = 0; a < 4; a++) {
        for (uint32_t b = 0; b < 4; b++) {
            total = 0;
            for (uint32_t i = 0; i < 4; i++) {
                total += data[a * 4 + i] * other.data[i * 4 + b];
            }
            mat.data[a * 4 + b] = total;
        }
    }
    return mat;
}

bool Mat44::operator==(Mat44 other) const {
    for (uint32_t a = 0; a < 4; a++) {
        for (uint32_t b = 0; b < 4; b++) {
            float total = data[a * 4 + b] - other.data[a * 4 + b];
            if (abs(total) > 0.5) {
                return false;
            }
        }
    }
    return true;
}

bool Mat44::operator!=(Mat44 other) const { return !((*this) == other); }

std::string Mat44::toString() const {
    std::string s;
    for (uint32_t a = 0; a < 4; a++) {
        s += "\n[";
        for (uint32_t b = 0; b < 4; b++) {
            if (b != 0) {
                s += ", " + std::to_string(data[a * 4 + b]);
            } else {
                s += std::to_string(data[a * 4 + b]);
            }
        }
        s += "]";
    }
    return s;
}

std::ostream &operator<<(std::ostream &os, Mat44 const &value) {
    os << value.toString();
    return os;
}

Mat44 Mat44::transpose() const {
    float data2[16];
    for (uint32_t r = 0; r < 4; r++) {
        for (uint32_t c = 0; c < 4; c++) {
            data2[c * 4 + r] = data[r * 4 + c];
        }
    }
    return Mat44(data2);
}

// Gaussian Elimination
Mat44 Mat44::inverse() const {
    Mat44 mat1;
    Mat44 mat2 = *this;

    float lead;
    float mul;

    for (uint32_t a = 0; a < 4; a++) {
        lead = mat2.data[a * 4 + a]; // find leadng number in row
        if (lead == 0) {
            // if leading number is 0 we must swap this row with one of the next
            // rows if this is notpossible there is no inverse matrix
            int swap = -1;
            for (uint32_t n = a + 1; n < 4; n++) {
                lead = mat2.data[n * 4 + n]; // find leadng number in row
                if (lead != 0) {
                    swap = n;
                    break;
                }
            }
            if (swap == -1) {
                std::cout << "Critical Error, matrix is not invertable\n";
                assert(false);
            }
            float temp[4];
            for (uint32_t c = 0; c < 4; c++) {
                temp[c] = mat2.data[swap * 4 + c];
                mat2.data[swap * 4 + c] = mat2.data[a * 4 + c];
                mat2.data[a * 4 + c] = temp[c];
            }
            for (uint32_t c = 0; c < 4; c++) {
                temp[c] = mat1.data[swap * 4 + c];
                mat1.data[swap * 4 + c] = mat1.data[a * 4 + c];
                mat1.data[a * 4 + c] = temp[c];
            }
        }

        lead = mat2.data[a * 4 + a]; // find leadng number in row
        for (uint32_t i = 0; i < 4; i++) {
            mat2.data[a * 4 + i] =
                mat2.data[a * 4 + i] / lead; // divide elements in row by lead
            mat1.data[a * 4 + i] = mat1.data[a * 4 + i] / lead;
        }

        for (uint32_t b = 0; b < 4; b++) {
            if (b == a) {
                continue;
            }
            mul = mat2.data[(b + 0) * 4 + a];
            for (uint32_t i = 0; i < 4; i++) {
                mat2.data[b * 4 + i] =
                    mat2.data[b * 4 + i] - mul * mat2.data[a * 4 + i];
                mat1.data[b * 4 + i] =
                    mat1.data[b * 4 + i] - mul * mat1.data[a * 4 + i];
            }
        }
    }
    return mat1;
}

// vectors are (x,y,z,0)
Vec3 Mat44::transformVector(Vec3 pnt) const {
    float a, b, c;
    a = pnt.x * data[0 * 4 + 0] + pnt.y * data[0 * 4 + 1] +
        pnt.z * data[0 * 4 + 2];
    b = pnt.x * data[1 * 4 + 0] + pnt.y * data[1 * 4 + 1] +
        pnt.z * data[1 * 4 + 2];
    c = pnt.x * data[2 * 4 + 0] + pnt.y * data[2 * 4 + 1] +
        pnt.z * data[2 * 4 + 2];
    return Vec3(a, b, c);
}

// points are (x,y,z,1)
Vec3 Mat44::transformPoint(Vec3 pnt) const {
    float a;
    float b;
    float c;
    float w;
    a = pnt.x * data[0 * 4 + 0] + pnt.y * data[0 * 4 + 1] +
        pnt.z * data[0 * 4 + 2] + data[0 * 4 + 3];
    b = pnt.x * data[1 * 4 + 0] + pnt.y * data[1 * 4 + 1] +
        pnt.z * data[1 * 4 + 2] + data[1 * 4 + 3];
    c = pnt.x * data[2 * 4 + 0] + pnt.y * data[2 * 4 + 1] +
        pnt.z * data[2 * 4 + 2] + data[2 * 4 + 3];
    w = pnt.x * data[3 * 4 + 0] + pnt.y * data[3 * 4 + 1] +
        pnt.z * data[3 * 4 + 2] + data[3 * 4 + 3];

    return Vec3(a / w, b / w, c / w);
}

// normals are multiplied by the transpose of the inverse matrix
Vec3 Mat44::transformNormal(Vec3 normal) const {
    Mat44 mat = *this;
    mat = mat.inverse().transpose();
    return mat.transformPoint(normal);
}

TEST_CASE("Matrix Multiplication is tested", "[Mat44]") {
    float a[16] = {1, 2, 3, 4, 5, 6, 7, 8, -1, -2, -5, -5, 6, 2, 18, 2};
    float b[16] = {1, 19, 2, 4, 6, 18, 22, -4, -6, 7, 55, 3, -4, -13, 9, 10};
    float c[16] = {-21, 24,  247,  45,  -33, 148, 599,  97,
                   37,  -25, -366, -61, -98, 250, 1064, 90};
    REQUIRE(Mat44(a) * Mat44(b) == Mat44(c));
}

TEST_CASE("Inverse matrices are checked.", "[Mat44]") {
    float a[16] = {1, 2, 4, 9, 2, 4, 2, 4, 7, 7, 7, 7, -6, 3, 3, 3};
    Mat44 mat1 = Mat44(a);
    REQUIRE(mat1 == mat1.inverse().inverse());
}

TEST_CASE("Transpose matrices are checked.", "[Mat44]") {
    float a[16] = {1, 2, 4, 9, 2, 4, 2, 4, 7, 7, 7, 7, -6, 3, 3, 3};
    Mat44 mat1 = Mat44(a);
    REQUIRE(mat1 == mat1.transpose().transpose());
}
