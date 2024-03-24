#include "sparse_matrix.hpp"
#include <cassert>

template <class T>
void SparseMatrix<T>::update_properties() {
    //reset number of non-zero elements and columns
    m_nnz = 0;
    m_m = 0;
    //loop over each row
    for(size_t i=0; i< m_data.size();++i){
        if (!m_data[i].empty()){  //check if the rows are empty
            m_nnz += m_data[i].size();
            m_m=std::max(m_m,m_data[i].size()); //""column size"" is the maximum number of elements in a row, expect a drawing on onenote when I come back (sorry :/)
        }
    }

}


template <class T>
std::ostream &operator<<(std::ostream &stream, SparseMatrix<T> &M) {
    //overloading of output operator
    //call update_properties method
    M.update_properties();
    //show the number of rows, cols, number of non-zero elements
    stream << "Number of rows: " << M.size() << std::endl; //M.size returns m_data.size(), very elaborate
    stream << "Minimum number of non-zero columns: " << M.m_m << std::endl;
    stream << "Number of non-zero elements" << M.m_nnz << std::endl;

    //print row-col index and value for each cell, such as:
    //A[i][j] = val; (like in matlab)

    for(size_t i = 0; i<M.m_data.size(); ++i){
        for(const auto & elem : M.m_data[i]){
            stream<< "A[" << i << "][" << elem.first << "]: "  << elem.second << std::endl;
        }
    }

}

//do I make the overloading operator a friend? cppreference -> operator overloading

template <class T>
void
SparseMatrix<T>::aij(std::vector<T>            &a,
                     std::vector<unsigned int> &i,
                     std::vector<unsigned int> &j) { 
    //converts sparse matrix to a different format (see pdf)
    //Update properties
    update_properties();
    //Convert to COO
    //first, resize the vectors, because we can (I reserve because I am too proud to change push_back, he has an iterator to the end (cringe))
    a.reserve(m_nnz);
    i.reserve(m_nnz);
    j.reserve(m_nnz);
    for(size_t h = 0; h<m_data.size();++h){
        for(auto elem=m_data[h].cbegin(); elem!=m_data[h].cend();++elem){ //we can also perform a loop with iterators
            a.push_back(elem->second);
            i.push_back(h);
            j.push_back(elem->first);
        }
    }
} 

template <class T>
void
SparseMatrix<T>::csr(std::vector<T>            &val,
                     std::vector<unsigned int> &col_ind,
                     std::vector<unsigned int> &row_ptr)
{
    //Converts sparse matrix to a different format (see pdf)
    //Update properties
    update_properties();
    //Convert to csr
    val.resize(m_nnz);
    col_ind.resize(m_nnz);
    row_ptr.reserve(size()+1);
    for(size_t h = 0; h<m_data.size();++h){ //yeah figure it out loool
        for(auto elem=m_data[h].cbegin(); elem!=m_data[h].cend();++elem){ //we can also perform a loop with iterators
            a.push_back(elem->second);
            i.push_back(h);
            j.push_back(elem->first);
        }
    }
}

template <class T>
void
SparseMatrix<T>::operator+=(SparseMatrix<T> &other)
{
    //Update the properties
    update_properties();
    //Check the dimensions
    assert(size()==other.size()); //assert does the same thing as an if loop, with automatic error handling
    for(size_t ii = 0; ii < other.size(); ++ii){
        for(const auto & el : other.m_data[ii]){
            (*this)[ii][el.first] += el.second;
        }
    }
}

template <class T>
std::vector<T>
operator*(SparseMatrix<T> &M, const std::vector<T> &x)
{
    //update the properties
    M.update_properties();
    //we assume the dimensions are correct
    //We perform the matrix dot product
}

//We must add a class specification for the template, otherwise the compiler will not be able to instantiate it
//in the main, we called SparseMatrix<double>, so we must add specializations for doubles here to prevent the compiler from complaining
// ...
//To prevent from having to do this, we must convert this cpp file into an hpp file, and inlcude a header guard (infnef, define, endif, ...)
//This way, we don't need to add specializations

// => IT'S A GOOD PRACTICE FOR TEMPLATE CLASSES TO BE HEADER ONLY!!!!!!