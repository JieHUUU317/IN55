#ifndef GLQUATERNION
#define GLQUATERNION
#include <QDebug>
#include "Vectors.h"
#include <qquaternion.h>


class GlQuaternion
{
private:
    float wp, xp, yp, zp;

public:
    /**
     * @brief Constructeur d'un quaternion
     */
    GlQuaternion();
    GlQuaternion(float scalar, float xpos, float ypos, float zpos);
    GlQuaternion(float scalar, const AbstractVec3<float32>& avector);

    /**
     * @brief isNull
     * @return Si le quaternion est nul
     */
    bool isNull() const;

    /**
     * @brief isIdentity
     * @return
     */
    bool isIdentity() const;

    /**
     * @brief getters and setters
     * @return x,y,z,w
     */
    float x() const;
    float y() const;
    float z() const;
    float scalar() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setScalar(float scalar);

    /**
     * @brief length
     * @return the length (square root of components) of the quaternion
     */
    float length() const;
    float lengthSquared() const;

    /**
     * @brief normalize the quaternion
     * @return
     */
    GlQuaternion normalized() const;

    void normalize();

    /**
     * @brief conjugate the quaternion
     * @return
     */
    GlQuaternion conjugate() const;

    /**
     * @brief rotatedVector
     * @param vecteur initial
     * @return  vector after rotation
     */
    AbstractVec3<float32> rotatedVector(const AbstractVec3<float32>& vector) const;

    AbstractVec3<float32> vector() const;

    void setVector(const AbstractVec3<float32>& aVector);

    void setVector(float aX, float aY, float aZ);

    /**
     * @brief operator overload
     * @param quaternion
     * @return
     */
    GlQuaternion &operator+=(const GlQuaternion &quaternion);
    GlQuaternion &operator-=(const GlQuaternion &quaternion);
    GlQuaternion &operator*=(float factor);
    GlQuaternion &operator*=(const GlQuaternion &quaternion);
    GlQuaternion &operator/=(float divisor);

    friend inline bool operator==(const GlQuaternion &q1, const GlQuaternion &q2);
    friend inline bool operator!=(const GlQuaternion &q1, const GlQuaternion &q2);
    friend inline const GlQuaternion operator+(const GlQuaternion &q1, const GlQuaternion &q2);
    friend inline const GlQuaternion operator-(const GlQuaternion &q1, const GlQuaternion &q2);
    friend inline const GlQuaternion operator*(float factor, const GlQuaternion &quaternion);
    friend inline const GlQuaternion operator*(const GlQuaternion &quaternion, float factor);
    friend inline const GlQuaternion operator*(const GlQuaternion &q1, const GlQuaternion &q2);
    friend inline const GlQuaternion operator-(const GlQuaternion &quaternion);
    friend inline const GlQuaternion operator/(const GlQuaternion &quaternion, float divisor);

    friend inline bool qFuzzyCompare(const GlQuaternion& q1, const GlQuaternion& q2);

    static GlQuaternion fromAxisAndAngle(const AbstractVec3<float32>& axis, float angle);

    static GlQuaternion fromAxisAndAngle(float x, float y, float z, float angle);

    static GlQuaternion slerp(const GlQuaternion& q1, const GlQuaternion& q2, float t);

    static GlQuaternion nlerp(const GlQuaternion& q1, const GlQuaternion& q2, float t);
};





inline GlQuaternion::GlQuaternion() : wp(1.0f), xp(0.0f), yp(0.0f), zp(0.0f) {}

inline GlQuaternion::GlQuaternion(float aScalar, float xpos, float ypos, float zpos) : wp(aScalar), xp(xpos), yp(ypos), zp(zpos) {}

inline GlQuaternion::GlQuaternion(float aScalar, const AbstractVec3<float32>& avector)
    : wp(aScalar), xp(avector.x), yp(avector.y), zp(avector.z) {}

inline bool GlQuaternion::isNull() const
{
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp) && qIsNull(wp);
}

inline bool GlQuaternion::isIdentity() const
{
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp) && wp == 1.0f;
}

inline float GlQuaternion::x() const { return xp; }
inline float GlQuaternion::y() const { return yp; }
inline float GlQuaternion::z() const { return zp; }
inline float GlQuaternion::scalar() const { return wp; }

inline void GlQuaternion::setX(float aX) { xp = aX; }
inline void GlQuaternion::setY(float aY) { yp = aY; }
inline void GlQuaternion::setZ(float aZ) { zp = aZ; }
inline void GlQuaternion::setScalar(float aScalar) { wp = aScalar; }
inline float GlQuaternion::length() const {return std::sqrt(wp*wp + xp * xp + yp * yp + zp * zp);}

inline GlQuaternion GlQuaternion::conjugate() const {return GlQuaternion(wp, -xp, -yp, -zp);}

inline void GlQuaternion::normalize(){
    float32 len = length();
    xp /= len;
    yp /= len;
    zp /= len;
    wp /= len;
}

inline GlQuaternion &GlQuaternion::operator+=(const GlQuaternion &quaternion)
{
    xp += quaternion.xp;
    yp += quaternion.yp;
    zp += quaternion.zp;
    wp += quaternion.wp;
    return *this;
}

inline GlQuaternion &GlQuaternion::operator-=(const GlQuaternion &quaternion)
{
    xp -= quaternion.xp;
    yp -= quaternion.yp;
    zp -= quaternion.zp;
    wp -= quaternion.wp;
    return *this;
}

inline GlQuaternion &GlQuaternion::operator*=(float factor)
{
    xp *= factor;
    yp *= factor;
    zp *= factor;
    wp *= factor;
    return *this;
}

inline const GlQuaternion operator*(const GlQuaternion &q1, const GlQuaternion& q2)
{
    float ww = (q1.zp + q1.xp) * (q2.xp + q2.yp);
    float yy = (q1.wp - q1.yp) * (q2.wp + q2.zp);
    float zz = (q1.wp + q1.yp) * (q2.wp - q2.zp);
    float xx = ww + yy + zz;
    float qq = 0.5 * (xx + (q1.zp - q1.xp) * (q2.xp - q2.yp));

    float w = qq - ww + (q1.zp - q1.yp) * (q2.yp - q2.zp);
    float x = qq - xx + (q1.xp + q1.wp) * (q2.xp + q2.wp);
    float y = qq - yy + (q1.wp - q1.xp) * (q2.yp + q2.zp);
    float z = qq - zz + (q1.zp + q1.yp) * (q2.wp - q2.xp);

    return GlQuaternion(w, x, y, z);
}

inline GlQuaternion &GlQuaternion::operator*=(const GlQuaternion &quaternion)
{
    *this = *this * quaternion;
    return *this;
}

inline GlQuaternion &GlQuaternion::operator/=(float divisor)
{
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    wp /= divisor;
    return *this;
}

inline bool operator==(const GlQuaternion &q1, const GlQuaternion &q2)
{
    return q1.xp == q2.xp && q1.yp == q2.yp && q1.zp == q2.zp && q1.wp == q2.wp;
}

inline bool operator!=(const GlQuaternion &q1, const GlQuaternion &q2)
{
    return q1.xp != q2.xp || q1.yp != q2.yp || q1.zp != q2.zp || q1.wp != q2.wp;
}

inline const GlQuaternion operator+(const GlQuaternion &q1, const GlQuaternion &q2)
{
    return GlQuaternion(q1.wp + q2.wp, q1.xp + q2.xp, q1.yp + q2.yp, q1.zp + q2.zp);
}

inline const GlQuaternion operator-(const GlQuaternion &q1, const GlQuaternion &q2)
{
    return GlQuaternion(q1.wp - q2.wp, q1.xp - q2.xp, q1.yp - q2.yp, q1.zp - q2.zp);
}

inline const GlQuaternion operator*(float factor, const GlQuaternion &quaternion)
{
    return GlQuaternion(quaternion.wp * factor, quaternion.xp * factor, quaternion.yp * factor, quaternion.zp * factor);
}

inline const GlQuaternion operator*(const GlQuaternion &quaternion, float factor)
{
    return GlQuaternion(quaternion.wp * factor, quaternion.xp * factor, quaternion.yp * factor, quaternion.zp * factor);
}

inline const GlQuaternion operator-(const GlQuaternion &quaternion)
{
    return GlQuaternion(-quaternion.wp, -quaternion.xp, -quaternion.yp, -quaternion.zp);
}

inline const GlQuaternion operator/(const GlQuaternion &quaternion, float divisor)
{
    return GlQuaternion(quaternion.wp / divisor, quaternion.xp / divisor, quaternion.yp / divisor, quaternion.zp / divisor);
}

inline bool qFuzzyCompare(const GlQuaternion& q1, const GlQuaternion& q2)
{
    return qFuzzyCompare(q1.xp, q2.xp) &&
           qFuzzyCompare(q1.yp, q2.yp) &&
           qFuzzyCompare(q1.zp, q2.zp) &&
           qFuzzyCompare(q1.wp, q2.wp);
}


inline void GlQuaternion::setVector(const AbstractVec3<float32>& aVector)
{
    xp = aVector.x;
    yp = aVector.y;
    zp = aVector.z;
}

inline AbstractVec3<float32> GlQuaternion::vector() const
{
    return AbstractVec3<float32>(xp, yp, zp);
}

inline void GlQuaternion::setVector(float aX, float aY, float aZ)
{
    xp = aX;
    yp = aY;
    zp = aZ;
}


#endif // GLQUATERNION

