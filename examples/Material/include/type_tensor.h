// $Id: type_tensor.h,v 1.4 2008/06/11 11:53:05 gdiso Exp $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2007  Benjamin S. Kirk, John W. Peterson

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __type_tensor_h__
#define __type_tensor_h__

// C++ includes
#include <cmath>

// Local includes
#include "genius_common.h"
#include "type_vector.h"




/**
 * This class defines a tensor in \p DIM dimensional space of type T.
 * T may either be Real or Complex.  The default constructor for
 * this class is protected, suggesting that you should not instantiate
 * one of these directly.
 *
 * \author Roy Stogner, 2004.
 */

template <typename T>
class TypeTensor
{
protected:

  /**
   * Constructor.  By default sets all entries to 0.  Gives the tensor 0 in
   * \p DIM dimensions.  This is a poor constructor for 2D tensors -
   * if the default arguments are to be overridden it requires that
   * the "z = 0." argument also be given explicitly.
   */
  TypeTensor  (const T xx=0.,
               const T xy=0.,
               const T xz=0.,
               const T yx=0.,
               const T yy=0.,
               const T yz=0.,
               const T zx=0.,
               const T zy=0.,
               const T zz=0.);
  /**
   * Construct Tensor by one vector. DIM==1 
   */
  TypeTensor  (const TypeVector<T> &x);
  
  /**
   * Construct Tensor by two vector. DIM==2 
   */
  TypeTensor  (const TypeVector<T> &x, const TypeVector<T> &y);
  
  /**
   * Construct Tensor by three  vector. DIM==3 
   */
  TypeTensor  (const TypeVector<T> &x, const TypeVector<T> &y, const TypeVector<T> &z);
public:

  /**
   * Copy-constructor.
   */
  TypeTensor(const TypeTensor<T>& p);

  /**
   * Destructor.
   */
  ~TypeTensor();

  /**
   * Assign to a tensor without creating a temporary.
   */
  void assign (const TypeTensor<T> &);

  /**
   * Return the \f$ i,j^{th} \f$ element of the tensor.
   */
  T operator () (const unsigned int i, const unsigned int j) const;

  /**
   * Return a writeable reference to the \f$ i,j^{th} \f$ element of the
   * tensor.
   */
  T & operator () (const unsigned int i, const unsigned int j);

  /**
   * Add two tensors. 
   */
  TypeTensor<T> operator + (const TypeTensor<T> &) const;

  /**
   * Add to this tensor. 
   */
  const TypeTensor<T> & operator += (const TypeTensor<T> &);

  /**
   * Add to this tensor without creating a temporary.
   */
  void add (const TypeTensor<T> &);

  /**
   * Add a scaled tensor to this tensor without
   * creating a temporary.
   */
  template <typename T2>
  void add_scaled (const TypeTensor<T2> &, const T);

  /**
   * Subtract two tensors.
   */
  TypeTensor<T> operator - (const TypeTensor<T> &) const;

  /**
   * Subtract from this tensor. 
   */
  const TypeTensor<T> & operator -= (const TypeTensor<T> &);

  /**
   * Subtract from this tensor without creating a temporary.
   */
  void subtract (const TypeTensor<T> &);

  /**
   * Subtract a scaled value from this tensor without
   * creating a temporary.
   */
  template <typename T2>
  void subtract_scaled (const TypeTensor<T2> &, const T);

  /**
   * Return the opposite of a tensor 
   */
  TypeTensor<T> operator - () const;

  /**
   * Multiply a tensor by a number, i.e. scale.
   */
  template <typename Scalar>
  typename boostcopy::enable_if_c<
  ScalarTraits<Scalar>::value,
  TypeTensor<T> >::type
  operator * (const Scalar) const;

  /**
   * Multiply this tensor by a number, i.e. scale.
   */
  template <typename Scalar>
  const TypeTensor<T> & operator *= (const Scalar);

  /**
   * Divide a tensor by a number, i.e. scale.
   */
  TypeTensor<T> operator / (const T) const;

  /**
   * Divide this tensor by a number, i.e. scale.
   */
  const TypeTensor<T> & operator /= (const T);

  /**
   * Multiply 2 tensors together, i.e. matrix product.
   * The tensors may be of different types.
   */
  template <typename T2>
  TypeTensor<T> operator * (const TypeTensor<T2> &) const;

  /**
   * Multiply 2 tensors together, i.e. sum Aij*Bij.
   * The tensors may be of different types.
   */
  template <typename T2>
  T contract (const TypeTensor<T2> &) const;

  /**
   * Multiply a tensor and vector together, i.e. matrix-vector product.
   * The tensor and vector may be of different types.
   */
  template <typename T2>
  TypeVector<T> operator * (const TypeVector<T2> &) const;

  /**
   * The transpose (with complex numbers not conjugated) of the tensor.
   */
  TypeTensor<T> transpose() const;

  /**
   * The det of the tensor.
   */
  T det() const;

  /**
   * Returns the Frobenius norm of the tensor, i.e. the square-root of
   * the sum of the elements squared.
   */
  T size() const;

  /**
   * Reutrns the Frobenius norm of the tensor squared, i.e. the
   * square-root of the sum of the elements squared.
   */
  T size_sq() const;

  /**
   * Zero the tensor in any dimension.
   */
  void zero();

  /**
   * @returns \p true if two tensors are equal valued.
   */
  bool operator == (const TypeTensor<T>& rhs) const;

  /**
   * @returns \p true if this tensor is "less"
   * than another.  Useful for sorting.
   */
  bool operator < (const TypeTensor<T>& rhs) const;

  /**
   * Formatted print to \p std::cout.
   */
  void print(std::ostream& os) const;

  /**
   * Formatted print as above but allows you to do
   * std::cout << t << std::endl;
   */
  friend std::ostream& operator << (std::ostream& os, const TypeTensor<T>& t)
  {
    t.print(os);
    return os;
  }

  /**
   * Unformatted print to the stream \p out.  Simply prints the elements
   * of the tensor separated by spaces and newlines.
   */
  void write_unformatted (std::ostream &out, const bool newline = true) const;

  // protected:

  /**
   * The coordinates of the \p TypeTensor
   */
  T _coords[DIM*DIM];
};



//------------------------------------------------------
// Inline functions
template <typename T>
inline
TypeTensor<T>::TypeTensor (const T xx,
                           const T xy,
                           const T xz,
                           const T yx,
                           const T yy,
                           const T yz,
                           const T zx,
                           const T zy,
                           const T zz)
{
  _coords[0] = xx;

  if (DIM == 2)
  {
    _coords[1] = xy;
    _coords[2] = yx;
    _coords[3] = yy;
  }

  if (DIM == 3)
  {
    _coords[1] = xy;
    _coords[2] = xz;
    _coords[3] = yx;
    _coords[4] = yy;
    _coords[5] = yz;
    _coords[6] = zx;
    _coords[7] = zy;
    _coords[8] = zz;
  }
}


template <typename T>
inline
TypeTensor<T>::TypeTensor  (const TypeVector<T> &x)
{
  genius_assert(DIM == 1);
  _coords[0] = x(0);
}

template <typename T>
inline
TypeTensor<T>::TypeTensor  (const TypeVector<T> &x, const TypeVector<T> &y)
{
  genius_assert(DIM == 2);
  _coords[0] = x(0);
  _coords[1] = x(1);
  _coords[2] = y(0);
  _coords[3] = y(1);
}


template <typename T>
inline
TypeTensor<T>::TypeTensor  (const TypeVector<T> &x, const TypeVector<T> &y, const TypeVector<T> &z)
{
  genius_assert(DIM == 3);
  _coords[0] = x(0);
  _coords[1] = x(1);
  _coords[2] = x(2);
  _coords[3] = y(0);
  _coords[4] = y(1);
  _coords[5] = y(2);
  _coords[6] = z(0);
  _coords[7] = z(1);
  _coords[8] = z(2);
}

template <typename T>
inline
TypeTensor<T>::TypeTensor (const TypeTensor <T> &p)
{
  // copy the nodes from vector p to me
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] = p._coords[i];
}



template <typename T>
inline
TypeTensor<T>::~TypeTensor ()
{}



template <typename T>
inline
void TypeTensor<T>::assign (const TypeTensor<T> &p)
{
  for (unsigned int i=0; i<DIM; i++)
    _coords[i] = p._coords[i];
}



template <typename T>
inline
T TypeTensor<T>::operator () (const unsigned int i,
                              const unsigned int j) const
{
  assert (i<3);
  assert (j<3);

#if DIM < 3
  if (i >= DIM || j >= DIM)
    return 0.;
#endif

  return _coords[i*DIM+j];
}



template <typename T>
inline
T & TypeTensor<T>::operator () (const unsigned int i,
                                const unsigned int j)
{
#if DIM < 3

  if (i >= DIM || j >= DIM)
  {
    //       std::cerr << "ERROR:  You are assigning to a tensor component" << std::endl
    // 		<< "that is out of range for the compiled DIM!"      << std::endl
    // 		<< " DIM=" << DIM << " , i=" << i << " , j=" << j << std::endl;
    genius_error();
  }

#endif

  assert (i<DIM);
  assert (j<DIM);

  return _coords[i*DIM+j];
}



template <typename T>
inline
TypeTensor<T> TypeTensor<T>::operator + (const TypeTensor<T> &p) const
{

#if DIM == 1
  return TypeTensor(_coords[0] + p._coords[0]);
#endif

#if DIM == 2
  return TypeTensor(_coords[0] + p._coords[0],
                    _coords[1] + p._coords[1],
                    0.,
                    _coords[2] + p._coords[2],
                    _coords[3] + p._coords[3]);
#endif

#if DIM == 3
  return TypeTensor(_coords[0] + p._coords[0],
                    _coords[1] + p._coords[1],
                    _coords[2] + p._coords[2],
                    _coords[3] + p._coords[3],
                    _coords[4] + p._coords[4],
                    _coords[5] + p._coords[5],
                    _coords[6] + p._coords[6],
                    _coords[7] + p._coords[7],
                    _coords[8] + p._coords[8]);
#endif

}



template <typename T>
inline
const TypeTensor<T> & TypeTensor<T>::operator += (const TypeTensor<T> &p)
{
  this->add (p);

  return *this;
}



template <typename T>
inline
void TypeTensor<T>::add (const TypeTensor<T> &p)
{
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] += p._coords[i];
}



template <typename T>
template <typename T2>
inline
void TypeTensor<T>::add_scaled (const TypeTensor<T2> &p, const T factor)
{
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] += factor*p._coords[i];

}



template <typename T>
inline
TypeTensor<T> TypeTensor<T>::operator - (const TypeTensor<T> &p) const
{

#if DIM == 1
  return TypeTensor(_coords[0] - p._coords[0]);
#endif

#if DIM == 2
  return TypeTensor(_coords[0] - p._coords[0],
                    _coords[1] - p._coords[1],
                    0.,
                    _coords[2] - p._coords[2],
                    _coords[3] - p._coords[3]);
#endif

#if DIM == 3
  return TypeTensor(_coords[0] - p._coords[0],
                    _coords[1] - p._coords[1],
                    _coords[2] - p._coords[2],
                    _coords[3] - p._coords[3],
                    _coords[4] - p._coords[4],
                    _coords[5] - p._coords[5],
                    _coords[6] - p._coords[6],
                    _coords[7] - p._coords[7],
                    _coords[8] - p._coords[8]);
#endif

}



template <typename T>
inline
const TypeTensor<T> & TypeTensor<T>::operator -= (const TypeTensor<T> &p)
{
  this->subtract (p);

  return *this;
}



template <typename T>
inline
void TypeTensor<T>::subtract (const TypeTensor<T>& p)
{
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] -= p._coords[i];
}



template <typename T>
template <typename T2>
inline
void TypeTensor<T>::subtract_scaled (const TypeTensor<T2> &p, const T factor)
{
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] -= factor*p._coords[i];
}



template <typename T>
inline
TypeTensor<T> TypeTensor<T>::operator - () const
{

#if DIM == 1
  return TypeTensor(-_coords[0]);
#endif

#if DIM == 2
  return TypeTensor(-_coords[0],
                    -_coords[1],
                    -_coords[2],
                    -_coords[3]);
#endif

#if DIM == 3
  return TypeTensor(-_coords[0],
                    -_coords[1],
                    -_coords[2],
                    -_coords[3],
                    -_coords[4],
                    -_coords[5],
                    -_coords[6],
                    -_coords[7],
                    -_coords[8]);
#endif

}



template <typename T>
template <typename Scalar>
inline
typename boostcopy::enable_if_c<
ScalarTraits<Scalar>::value,
TypeTensor<T> >::type
TypeTensor<T>::operator * (const Scalar factor) const
{

#if DIM == 1
  return TypeTensor(_coords[0]*factor);
#endif

#if DIM == 2
  return TypeTensor(_coords[0]*factor,
                    _coords[1]*factor,
                    _coords[2]*factor,
                    _coords[3]*factor);
#endif

#if DIM == 3
  return TypeTensor(_coords[0]*factor,
                    _coords[1]*factor,
                    _coords[2]*factor,
                    _coords[3]*factor,
                    _coords[4]*factor,
                    _coords[5]*factor,
                    _coords[6]*factor,
                    _coords[7]*factor,
                    _coords[8]*factor);
#endif
}



template <typename T, typename Scalar>
inline
typename boostcopy::enable_if_c<
ScalarTraits<Scalar>::value,
const TypeVector<T> >::type
operator * (const Scalar factor,
            const TypeTensor<T> &t)
{
  return t * factor;
}



template <typename T>
template <typename Scalar>
inline
const TypeTensor<T> & TypeTensor<T>::operator *= (const Scalar factor)
{
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] *= factor;

  return *this;
}




template <typename T>
inline
TypeTensor<T> TypeTensor<T>::operator / (const T factor) const
{
  assert (factor != static_cast<T>(0.));

#if DIM == 1
  return TypeTensor(_coords[0]/factor);
#endif

#if DIM == 2
  return TypeTensor(_coords[0]/factor,
                    _coords[1]/factor,
                    _coords[2]/factor,
                    _coords[3]/factor);
#endif

#if DIM == 3
  return TypeTensor(_coords[0]/factor,
                    _coords[1]/factor,
                    _coords[2]/factor,
                    _coords[3]/factor,
                    _coords[4]/factor,
                    _coords[5]/factor,
                    _coords[6]/factor,
                    _coords[7]/factor,
                    _coords[8]/factor);
#endif

}



template <typename T>
inline
TypeTensor<T> TypeTensor<T>::transpose() const
{
#if DIM == 1
  return TypeTensor(_coords[0]);
#endif

#if DIM == 2
  return TypeTensor(_coords[0],
                    _coords[2],
                    _coords[1],
                    _coords[3]);
#endif

#if DIM == 3
  return TypeTensor(_coords[0],
                    _coords[3],
                    _coords[6],
                    _coords[1],
                    _coords[4],
                    _coords[7],
                    _coords[2],
                    _coords[5],
                    _coords[8]);
#endif
}



template <typename T>
inline
const TypeTensor<T> & TypeTensor<T>::operator /= (const T factor)
{
  assert (factor != static_cast<T>(0.));

  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] /= factor;

  return *this;
}




template <typename T>
template <typename T2>
inline
TypeVector<T> TypeTensor<T>::operator * (const TypeVector<T2> &p) const
{
  TypeVector<T> returnval;
  for (unsigned int i=0; i<DIM; i++)
    for (unsigned int j=0; j<DIM; j++)
      returnval(i) += (*this)(i,j)*p(j);

  return returnval;
}



template <typename T>
template <typename T2>
inline
TypeTensor<T> TypeTensor<T>::operator * (const TypeTensor<T2> &p) const
{
  TypeTensor<T> returnval;
  for (unsigned int i=0; i<DIM; i++)
    for (unsigned int j=0; j<DIM; j++)
      for (unsigned int k=0; k<DIM; k++)
        returnval(i,j) += (*this)(i,k)*p(k,j);

  return returnval;
}



/**
 * Multiply 2 tensors together, i.e. sum Aij*Bij.
 * The tensors may be of different types.
 */
template <typename T>
template <typename T2>
inline
T TypeTensor<T>::contract (const TypeTensor<T2> &t) const
{
  T sum = 0.;
  for (unsigned int i=0; i<DIM*DIM; i++)
    sum += _coords[i]*t._coords[i];
  return sum;
}


template <typename T>
inline
T TypeTensor<T>::det() const
{
  T Det;
  Det = _coords[0] * _coords[4] * _coords[8]
     -  _coords[0] * _coords[5] * _coords[7]
     +  _coords[1] * _coords[5] * _coords[6]
     -  _coords[1] * _coords[3] * _coords[8]
     +  _coords[2] * _coords[3] * _coords[7]
     -  _coords[2] * _coords[4] * _coords[6]
     ;
  return Det;
}


template <typename T>
inline
T TypeTensor<T>::size() const
{
  return sqrt(this->size_sq());
}



template <typename T>
inline
void TypeTensor<T>::zero()
{
  for (unsigned int i=0; i<DIM*DIM; i++)
    _coords[i] = 0.;
}



template <typename T>
inline
T TypeTensor<T>::size_sq () const
{
  T sum = 0.;
  for (unsigned int i=0; i<DIM*DIM; i++)
    sum += _coords[i]*_coords[i];
  return sum;
}




template <typename T>
inline
bool TypeTensor<T>::operator == (const TypeTensor<T>& rhs) const
{
#if DIM == 1
  return (fabs(_coords[0] - rhs._coords[0])
          < TOLERANCE);
#endif

#if DIM == 2
  return ((fabs(_coords[0] - rhs._coords[0]) +
           fabs(_coords[1] - rhs._coords[1]) +
           fabs(_coords[2] - rhs._coords[2]) +
           fabs(_coords[3] - rhs._coords[3]))
          < 4.*TOLERANCE);
#endif

#if DIM == 3
  return ((fabs(_coords[0] - rhs._coords[0]) +
           fabs(_coords[1] - rhs._coords[1]) +
           fabs(_coords[2] - rhs._coords[2]) +
           fabs(_coords[3] - rhs._coords[3]) +
           fabs(_coords[4] - rhs._coords[4]) +
           fabs(_coords[5] - rhs._coords[5]) +
           fabs(_coords[6] - rhs._coords[6]) +
           fabs(_coords[7] - rhs._coords[7]) +
           fabs(_coords[8] - rhs._coords[8]))
          < 9.*TOLERANCE);
#endif

}




#endif // #define __type_tensor_h__
