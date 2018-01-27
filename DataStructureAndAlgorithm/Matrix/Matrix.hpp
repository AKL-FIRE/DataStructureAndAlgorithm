//
//  Matrix.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 26/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "../Tool/utlity.h"

template <typename T>
class matrix
{
public:
    matrix(int theRows = 0, int theColumns = 0);
    matrix(int, int, T*);
    matrix(const matrix<T>&);
    ~matrix() {delete [] element;}
    int rows() const {return theRows;}
    int columns() const {return theColumns;}
    T& operator()(int i, int j) const;
    matrix<T>& operator=(const matrix<T>&);
    matrix<T> operator+(const T&) const;
    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-(const T&) const;
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const T&) const;
    matrix<T> operator*(const matrix<T>&) const;
    matrix<T> operator/(const T&) const;
    matrix<T>& operator+=(const T&);
    matrix<T>& operator-=(const T&);
    matrix<T>& operator*=(const T&);
    matrix<T> transpose();
    T det() const;
    matrix<T> inv() const;
    
    template <typename M>
    friend std::ostream& operator<<(std::ostream&, const matrix<M>&); //Because friend function is not a member function.
    
private:
    int theRows, theColumns;
    T *element;
};

template <typename T>
matrix<T>::matrix(int theRows, int theColumns)
{
    if(theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue("Either both or neiter rows and columns should be zaros");
    
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];
}

template <typename T>
matrix<T>::matrix(int theRows, int theColumns, T *e)
{
    if(theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue("Either both or neiter rows and columns should be zaros");
    
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];
    std::copy(e, e + theRows * theColumns, element);
}

template <typename T>
matrix<T>::matrix(const matrix<T> &m)
{
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T[theRows * theColumns];
    std::copy(m.element, m.element + theRows * theColumns, element);
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const matrix<T> &m)
{
    for(int i = 0; i < m.theRows * m.theColumns; i++)
    {
        if(i % m.rows() == 0)
            out << std::endl;
        out << m.element[i] << ",";
    }
    return out;
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T> &m)
{
    if(this != &m)
    {
        delete [] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T[theRows * theColumns];
        std::copy(m.element, m.element + theRows * theColumns, element);
    }
    return *this;
}

template <typename T>
T& matrix<T>::operator()(int i, int j) const
{
    if(i < 1 || i > theRows || j < 1 || j > theColumns)
        throw illegalParameterValue("i, j out of bounds");
    return element[(i - 1) * theColumns + j - 1];
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &m) const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw illegalParameterValue("The two matrices must have the same size.");
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] + m.element[i];
    return w;
}

template <typename T>
matrix<T> matrix<T>::operator+(const T &m) const
{
    matrix<T> w(*this);
    for(int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] + m;
    return w;
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &m) const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw illegalParameterValue("The two matrices must have the same size.");
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] - m.element[i];
    return w;
}

template <typename T>
matrix<T> matrix<T>::operator-(const T &m) const
{
    matrix<T> w(*this);
    for(int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] - m;
    return w;
}

template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &m) const
{
    if(theColumns != m.theRows)
        throw illegalParameterValue("The first matrix's columns must be equal to the second matrix's rows");
    matrix<T> w(theRows, m.theColumns);
    int ct = 0, cm = 0, cw = 0;
    for(int i = 1; i <= theRows; i++)
    {
        for(int j = 1; j <= m.theColumns; j++)
        {
            T sum = element[ct] * m.element[cm];
            for(int k = 2; k <= theColumns; k++)
            {
                ct++;
                cm += m.theColumns;
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum;
            ct -= theColumns - 1;
            cm = j;
        }
        ct += theColumns;
        cm = 0;
    }
    return w;
}

template <typename T>
matrix<T> matrix<T>::operator*(const T &m) const
{
    matrix<T> w(*this);
    for(int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] * m;
    return w;
}

template <typename T>
matrix<T> matrix<T>::operator/(const T  &m) const
{
    matrix<T> w(*this);
    for(int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] / m;
    return w;
}

template <typename T>
matrix<T>& matrix<T>::operator+=(const T &m)
{
    for(int i = 0; i < theRows * theColumns; i++)
        element[i] += m;
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator-=(const T &m)
{
    for(int i = 0; i < theRows * theColumns; i++)
        element[i] -= m;
    return *this;
}

template <typename T>
matrix<T>& matrix<T>::operator*=(const T &m)
{
    for(int i = 0; i < theRows * theColumns; i++)
        element[i] *= m;
    return *this;
}

template <typename T>
matrix<T> matrix<T>::transpose()
{
    matrix<T> w(theColumns, theRows);
    for(int i = 1; i <= theRows ; i++)
        for(int j = 1; j <= theColumns ; j++)
            w(j,i) = this->operator()(i, j);
    return w;
}

template <typename T>
T matrix<T>::det() const
{
    if(theRows != theColumns)
        throw illegalParameterValue("The rows of matrix must be equal to the columns of matrix");
}
#endif /* Matrix_hpp */
