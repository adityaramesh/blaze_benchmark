//=================================================================================================
/*!
//  \file src/mathtest/sparsesubmatrix/ClassTest.cpp
//  \brief Source file for the SparseSubmatrix class test
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blaze/math/DynamicMatrix.h>
#include <blaze/math/Views.h>
#include <blazetest/mathtest/sparsesubmatrix/ClassTest.h>


namespace blazetest {

namespace mathtest {

namespace sparsesubmatrix {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the SparseSubmatrix class test.
//
// \exception std::runtime_error Operation error detected.
*/
ClassTest::ClassTest()
   : mat_ ( 5UL, 4UL )
   , tmat_( 4UL, 5UL )
{
   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testMultAssign();
   testScaling();
   testFunctionCall();
   testIterator();
   testNonZeros();
   testReset();
   testClear();
   testSet();
   testInsert();
   testAppend();
   testErase();
   testReserve();
   testTrim();
   testTranspose();
   testFind();
   testLowerBound();
   testUpperBound();
   testIsDefault();
   testIsSame();
   testSubmatrix();
   testRow();
   testColumn();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the SparseSubmatrix class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testConstructors()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix constructor";

      initialize();

      for( size_t row=0UL; row<mat_.rows(); ++row ) {
         for( size_t column=0UL; column<mat_.columns(); ++column ) {
            for( size_t m=1UL; (row+m)<mat_.rows(); ++m ) {
               for( size_t n=1UL; (column+n)<mat_.columns(); ++n )
               {
                  SMT sm = submatrix( mat_, row, column, m, n );

                  for( size_t i=0UL; i<m; ++i ) {
                     for( size_t j=0UL; j<n; ++j )
                     {
                        if( sm(i,j) != mat_(row+i,column+j) ) {
                           std::ostringstream oss;
                           oss << " Test: " << test_ << "\n"
                               << " Error: Setup of sparse submatrix failed\n"
                               << " Details:\n"
                               << "   Index of first row    = " << row << "\n"
                               << "   Index of first column = " << column << "\n"
                               << "   Number of rows        = " << m << "\n"
                               << "   Number of columns     = " << n << "\n"
                               << "   Submatrix:\n" << sm << "\n"
                               << "   Matrix:\n" << mat_ << "\n";
                           throw std::runtime_error( oss.str() );
                        }
                     }
                  }
               }
            }
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix constructor";

      initialize();

      for( size_t column=0UL; column<tmat_.columns(); ++column ) {
         for( size_t row=0UL; row<tmat_.rows(); ++row ) {
            for( size_t n=1UL; (column+n)<tmat_.columns(); ++n ) {
               for( size_t m=1UL; (row+m)<tmat_.rows(); ++m )
               {
                  OSMT sm = submatrix( tmat_, row, column, m, n );

                  for( size_t j=0UL; j<n; ++j ) {
                     for( size_t i=0UL; i<m; ++i )
                     {
                        if( sm(i,j) != tmat_(row+i,column+j) ) {
                           std::ostringstream oss;
                           oss << " Test: " << test_ << "\n"
                               << " Error: Setup of sparse submatrix failed\n"
                               << " Details:\n"
                               << "   Index of first row    = " << row << "\n"
                               << "   Index of first column = " << column << "\n"
                               << "   Number of rows        = " << m << "\n"
                               << "   Number of columns     = " << n << "\n"
                               << "   Submatrix:\n" << sm << "\n"
                               << "   Matrix:\n" << tmat_ << "\n";
                           throw std::runtime_error( oss.str() );
                        }
                     }
                  }
               }
            }
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAssignment()
{
   //=====================================================================================
   // Row-major copy assignment
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix copy assignment (no aliasing)";

      initialize();

      MT mat( 5UL, 4UL, 3UL );
      mat(1,0) = 11;
      mat(2,0) = 12;
      mat(2,2) = 13;

      SMT sm = submatrix( mat, 1UL, 0UL, 2UL, 3UL );
      sm = submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );
      checkRows    ( mat ,  5UL );
      checkColumns ( mat ,  4UL );
      checkNonZeros( mat ,  4UL );

      if( sm(0,0) != 0 || sm(0,1) != -3 || sm(0,2) !=  0 ||
          sm(1,0) != 4 || sm(1,1) !=  5 || sm(1,2) != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -3  0 )\n( 4  5 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) != 0 || mat(0,1) !=  0 || mat(0,2) !=  0 || mat(0,3) != 0 ||
          mat(1,0) != 0 || mat(1,1) != -3 || mat(1,2) !=  0 || mat(1,3) != 0 ||
          mat(2,0) != 4 || mat(2,1) !=  5 || mat(2,2) != -6 || mat(2,3) != 0 ||
          mat(3,0) != 0 || mat(3,1) !=  0 || mat(3,2) !=  0 || mat(3,3) != 0 ||
          mat(4,0) != 0 || mat(4,1) !=  0 || mat(4,2) !=  0 || mat(4,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0 -3  0  0 )\n"
                                     "( 4  5 -6  0 )\n"
                                     "( 0  0  0  0 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major SparseSubmatrix copy assignment (aliasing)";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );
      sm = submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      /*
      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );
      */

      if( sm(0,0) != 0 || sm(0,1) != -3 || sm(0,2) !=  0 ||
          sm(1,0) != 4 || sm(1,1) !=  5 || sm(1,2) != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -3  0 )\n( 4  5 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) != -3 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 4 || mat_(2,1) !=  5 || mat_(2,2) != -6 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0 -3  0  0 )\n"
                                     "( 4  5 -6  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 3UL, 0 );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm = mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 11 || sm(0,2) !=  0 ||
          sm(1,0) != 12 || sm(1,1) != 13 || sm(1,2) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 11  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 11 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 12 || mat_(2,1) != 13 || mat_(2,2) != 14 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 11  0  0 )\n"
                                     "( 12 13 14  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 3UL, 0 );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm = mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 11 || sm(0,2) !=  0 ||
          sm(1,0) != 12 || sm(1,1) != 13 || sm(1,2) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 11  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 11 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 12 || mat_(2,1) != 13 || mat_(2,2) != 14 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 11  0  0 )\n"
                                     "( 12 13 14  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 3UL, 4UL );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm = mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 11 || sm(0,2) !=  0 ||
          sm(1,0) != 12 || sm(1,1) != 13 || sm(1,2) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 11  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 11 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 12 || mat_(2,1) != 13 || mat_(2,2) != 14 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 11  0  0 )\n"
                                     "( 12 13 14  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 3UL, 4UL );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm = mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 11 || sm(0,2) !=  0 ||
          sm(1,0) != 12 || sm(1,1) != 13 || sm(1,2) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 11  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 11 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 12 || mat_(2,1) != 13 || mat_(2,2) != 14 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 11  0  0 )\n"
                                     "( 12 13 14  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy assignment
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix copy assignment (no aliasing)";

      initialize();

      OMT mat( 4UL, 5UL, 3UL );
      mat(0,1) = 11;
      mat(0,2) = 12;
      mat(2,2) = 13;

      OSMT sm = submatrix( mat, 0UL, 1UL, 3UL, 2UL );
      sm = submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );
      checkRows    ( mat  ,  4UL );
      checkColumns ( mat  ,  5UL );
      checkNonZeros( mat  ,  4UL );

      if( sm(0,0) !=  0 || sm(0,1) !=  4 ||
          sm(1,0) != -3 || sm(1,1) !=  5 ||
          sm(2,0) !=  0 || sm(2,1) != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  4 )\n( -3  5 )\n(  0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) != 0 || mat(0,1) !=  0 || mat(0,2) !=  4 || mat(0,3) != 0 || mat(0,4) != 0 ||
          mat(1,0) != 0 || mat(1,1) != -3 || mat(1,2) !=  5 || mat(1,3) != 0 || mat(1,4) != 0 ||
          mat(2,0) != 0 || mat(2,1) !=  0 || mat(2,2) != -6 || mat(2,3) != 0 || mat(2,4) != 0 ||
          mat(3,0) != 0 || mat(3,1) !=  0 || mat(3,2) !=  0 || mat(3,3) != 0 || mat(3,4) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n( 0  0  4  0  0 )\n"
                                     "( 0 -3  5  0  0 )\n"
                                     "( 0  0 -6  0  0 )\n"
                                     "( 0  0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major SparseSubmatrix copy assignment (aliasing)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );
      sm = submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) !=  4 ||
          sm(1,0) != -3 || sm(1,1) !=  5 ||
          sm(2,0) !=  0 || sm(2,1) != -6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  4 )\n( -3  5 )\n(  0 -6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  4 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != -3 || tmat_(1,2) !=  5 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -6 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0  4  0  7 )\n"
                                     "( 0 -3  5  4 -8 )\n"
                                     "( 0  0 -6  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 2UL, 0 );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm = mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 ||
          sm(1,0) != 11 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12 )\n( 11 13 )\n(  0 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 12 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 14 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 12  0  7 )\n"
                                     "( 0 11 13  4 -8 )\n"
                                     "( 0  0 14  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 2UL, 0 );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm = mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 ||
          sm(1,0) != 11 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12 )\n( 11 13 )\n(  0 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 12 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 14 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 12  0  7 )\n"
                                     "( 0 11 13  4 -8 )\n"
                                     "( 0  0 14  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 2UL, 4UL );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm = mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 ||
          sm(1,0) != 11 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12 )\n( 11 13 )\n(  0 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 12 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 14 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 12  0  7 )\n"
                                     "( 0 11 13  4 -8 )\n"
                                     "( 0  0 14  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 2UL, 4UL );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm = mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 ||
          sm(1,0) != 11 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 14 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12 )\n( 11 13 )\n(  0 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 12 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 14 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 12  0  7 )\n"
                                     "( 0 11 13  4 -8 )\n"
                                     "( 0  0 14  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the SparseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAddAssign()
{
   //=====================================================================================
   // Row-major SparseSubmatrix addition assignment
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix addition assignment (no aliasing)";

      initialize();

      MT mat( 5UL, 4UL, 3UL );
      mat(1,0) = 11;
      mat(2,0) = 12;
      mat(2,2) = 13;

      SMT sm = submatrix( mat, 1UL, 0UL, 2UL, 3UL );
      sm += submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  5UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );
      checkRows    ( mat ,  5UL );
      checkColumns ( mat ,  4UL );
      checkNonZeros( mat ,  5UL );

      if( sm(0,0) != 11 || sm(0,1) != -3 || sm(0,2) != 0 ||
          sm(1,0) != 16 || sm(1,1) !=  5 || sm(1,2) != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 11 -3  0 )\n( 16  5  7 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) !=  0 || mat(0,1) !=  0 || mat(0,2) != 0 || mat(0,3) != 0 ||
          mat(1,0) != 11 || mat(1,1) != -3 || mat(1,2) != 0 || mat(1,3) != 0 ||
          mat(2,0) != 16 || mat(2,1) !=  5 || mat(2,2) != 7 || mat(2,3) != 0 ||
          mat(3,0) !=  0 || mat(3,1) !=  0 || mat(3,2) != 0 || mat(3,3) != 0 ||
          mat(4,0) !=  0 || mat(4,1) !=  0 || mat(4,2) != 0 || mat(4,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( 11 -3  0  0 )\n"
                                     "( 16  5  7  0 )\n"
                                     "(  0  0  0  0 )\n"
                                     "(  0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major SparseSubmatrix addition assignment (aliasing)";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );
      sm += submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) !=  0 ||
          sm(1,0) != 2 || sm(1,1) !=  5 || sm(1,2) != -9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 2  5 -9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) != -2 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 2 || mat_(2,1) !=  5 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 0 -2  0  0 )\n"
                                     "( 2  5 -9  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix addition assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix addition assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 3UL, 0 );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm += mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 10 13 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix addition assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 3UL, 0 );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm += mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 10 13 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix addition assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix addition assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 3UL, 4UL );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm += mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 10 13 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix addition assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 3UL, 4UL );
      mat(0,1) = 11;
      mat(1,0) = 12;
      mat(1,1) = 13;
      mat(1,2) = 14;

      sm += mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 10 13 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major SparseSubmatrix addition assignment
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix addition assignment (no aliasing)";

      initialize();

      OMT mat( 4UL, 5UL, 3UL );
      mat(0,1) = 11;
      mat(0,2) = 12;
      mat(2,2) = 13;

      OSMT sm = submatrix( mat, 0UL, 1UL, 3UL, 2UL );
      sm += submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  5UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );
      checkRows    ( mat  ,  4UL );
      checkColumns ( mat  ,  5UL );
      checkNonZeros( mat  ,  5UL );

      if( sm(0,0) != 11 || sm(0,1) != 16 ||
          sm(1,0) != -3 || sm(1,1) !=  5 ||
          sm(2,0) !=  0 || sm(2,1) !=  7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 11 16 )\n( -3  5 )\n(  0  7 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) != 0 || mat(0,1) != 11 || mat(0,2) != 16 || mat(0,3) != 0 || mat(0,4) != 0 ||
          mat(1,0) != 0 || mat(1,1) != -3 || mat(1,2) !=  5 || mat(1,3) != 0 || mat(1,4) != 0 ||
          mat(2,0) != 0 || mat(2,1) !=  0 || mat(2,2) !=  7 || mat(2,3) != 0 || mat(2,4) != 0 ||
          mat(3,0) != 0 || mat(3,1) !=  0 || mat(3,2) !=  0 || mat(3,3) != 0 || mat(3,4) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n( 0 11 16  0  0 )\n"
                                     "( 0 -3  5  0  0 )\n"
                                     "( 0  0  7  0  0 )\n"
                                     "( 0  0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major SparseSubmatrix addition assignment (aliasing)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );
      sm += submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) !=  2 ||
          sm(1,0) != -2 || sm(1,1) !=  5 ||
          sm(2,0) !=  0 || sm(2,1) != -9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  2 )\n( -2  5 )\n(  0 -9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) !=  2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != -2 || tmat_(1,2) !=  5 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -9 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0  2  0  7 )\n"
                                     "( 0 -2  5  4 -8 )\n"
                                     "( 0  0 -9  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix addition assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix addition assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 2UL, 0 );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm += mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix addition assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 2UL, 0 );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm += mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix addition assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix addition assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 2UL, 4UL );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm += mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix addition assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 2UL, 4UL );
      mat(1,0) = 11;
      mat(0,1) = 12;
      mat(1,1) = 13;
      mat(2,1) = 14;

      sm += mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the SparseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testSubAssign()
{
   //=====================================================================================
   // Row-major SparseSubmatrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix subtraction assignment (no aliasing)";

      initialize();

      MT mat( 5UL, 4UL, 3UL );
      mat(1,0) = 11;
      mat(2,0) = 12;
      mat(2,2) = 13;

      SMT sm = submatrix( mat, 1UL, 0UL, 2UL, 3UL );
      sm -= submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  5UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );
      checkRows    ( mat ,  5UL );
      checkColumns ( mat ,  4UL );
      checkNonZeros( mat ,  5UL );

      if( sm(0,0) != 11 || sm(0,1) !=  3 || sm(0,2) !=  0 ||
          sm(1,0) !=  8 || sm(1,1) != -5 || sm(1,2) != 19 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 11  3  0 )\n(  8 -5 19 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) !=  0 || mat(0,1) !=  0 || mat(0,2) !=  0 || mat(0,3) != 0 ||
          mat(1,0) != 11 || mat(1,1) !=  3 || mat(1,2) !=  0 || mat(1,3) != 0 ||
          mat(2,0) !=  8 || mat(2,1) != -5 || mat(2,2) != 19 || mat(2,3) != 0 ||
          mat(3,0) !=  0 || mat(3,1) !=  0 || mat(3,2) !=  0 || mat(3,3) != 0 ||
          mat(4,0) !=  0 || mat(4,1) !=  0 || mat(4,2) !=  0 || mat(4,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( 11  3  0  0 )\n"
                                     "(  8 -5 19  0 )\n"
                                     "(  0  0  0  0 )\n"
                                     "(  0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major SparseSubmatrix subtraction assignment (aliasing)";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );
      sm -= submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) !=  4 || sm(0,2) != 0 ||
          sm(1,0) != -6 || sm(1,1) != -5 || sm(1,2) != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  4  0 )\n( -6 -5  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  4 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) != -5 || mat_(2,2) != 3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  4  0  0 )\n"
                                     "( -6 -5  3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix subtraction assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 3UL, 0 );
      mat(0,1) = -11;
      mat(1,0) = -12;
      mat(1,1) = -13;
      mat(1,2) = -14;

      sm -= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix subtraction assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 3UL, 0 );
      mat(0,1) = -11;
      mat(1,0) = -12;
      mat(1,1) = -13;
      mat(1,2) = -14;

      sm -= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 10 13 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix subtraction assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 3UL, 4UL );
      mat(0,1) = -11;
      mat(1,0) = -12;
      mat(1,1) = -13;
      mat(1,2) = -14;

      sm -= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix subtraction assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 3UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 3UL, 4UL );
      mat(0,1) = -11;
      mat(1,0) = -12;
      mat(1,1) = -13;
      mat(1,2) = -14;

      sm -= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 12 || sm(0,2) !=  0 ||
          sm(1,0) != 10 || sm(1,1) != 13 || sm(1,2) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 12  0 )\n( 12 13 14 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) != 12 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 10 || mat_(2,1) != 13 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 12  0  0 )\n"
                                     "( 10 13 11  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major SparseSubmatrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix subtraction assignment (no aliasing)";

      initialize();

      OMT mat( 4UL, 5UL, 3UL );
      mat(0,1) = 11;
      mat(0,2) = 12;
      mat(2,2) = 13;

      OSMT sm = submatrix( mat, 0UL, 1UL, 3UL, 2UL );
      sm -= submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  5UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );
      checkRows    ( mat  ,  4UL );
      checkColumns ( mat  ,  5UL );
      checkNonZeros( mat  ,  5UL );

      if( sm(0,0) != 11 || sm(0,1) !=  8 ||
          sm(1,0) !=  3 || sm(1,1) != -5 ||
          sm(2,0) !=  0 || sm(2,1) != 19 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 11  8 )\n(  3 -5 )\n(  0 19 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) != 0 || mat(0,1) != 11 || mat(0,2) !=  8 || mat(0,3) != 0 || mat(0,4) != 0 ||
          mat(1,0) != 0 || mat(1,1) !=  3 || mat(1,2) != -5 || mat(1,3) != 0 || mat(1,4) != 0 ||
          mat(2,0) != 0 || mat(2,1) !=  0 || mat(2,2) != 19 || mat(2,3) != 0 || mat(2,4) != 0 ||
          mat(3,0) != 0 || mat(3,1) !=  0 || mat(3,2) !=  0 || mat(3,3) != 0 || mat(3,4) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n( 0 11  8  0  0 )\n"
                                     "( 0  3 -5  0  0 )\n"
                                     "( 0  0 19  0  0 )\n"
                                     "( 0  0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major SparseSubmatrix subtraction assignment (aliasing)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );
      sm -= submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) != 0 || sm(0,1) != -6 ||
          sm(1,0) != 4 || sm(1,1) != -5 ||
          sm(2,0) != 0 || sm(2,1) !=  3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -6 )\n( 4 -5 )\n( 0  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 4 || tmat_(1,2) != -5 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) !=  3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  7 )\n"
                                     "( 0  4 -5  4 -8 )\n"
                                     "( 0  0  3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix subtraction assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 2UL, 0 );
      mat(1,0) = -11;
      mat(0,1) = -12;
      mat(1,1) = -13;
      mat(2,1) = -14;

      sm -= mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix subtraction assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 2UL, 0 );
      mat(1,0) = -11;
      mat(0,1) = -12;
      mat(1,1) = -13;
      mat(2,1) = -14;

      sm -= mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix subtraction assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix subtraction assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 2UL, 4UL );
      mat(1,0) = -11;
      mat(0,1) = -12;
      mat(1,1) = -13;
      mat(2,1) = -14;

      sm -= mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix subtraction assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 2UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 2UL, 4UL );
      mat(1,0) = -11;
      mat(0,1) = -12;
      mat(1,1) = -13;
      mat(2,1) = -14;

      sm -= mat;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) !=  0 || sm(0,1) != 10 ||
          sm(1,0) != 12 || sm(1,1) != 13 ||
          sm(2,0) !=  0 || sm(2,1) != 11 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 10 )\n( 12 13 )\n(  0 11 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 12 || tmat_(1,2) != 13 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 10  0  7 )\n"
                                     "( 0 12 13  4 -8 )\n"
                                     "( 0  0 11  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the SparseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMultAssign()
{
   //=====================================================================================
   // Row-major SparseSubmatrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix multiplication assignment (no aliasing)";

      initialize();

      MT mat( 5UL, 4UL, 4UL );
      mat(1,0) = 1;
      mat(1,1) = 1;
      mat(2,0) = 1;
      mat(2,1) = 1;

      SMT sm = submatrix( mat, 1UL, 0UL, 2UL, 2UL );
      sm *= submatrix( mat_, 2UL, 1UL, 2UL, 2UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );
      checkRows    ( mat ,  5UL );
      checkColumns ( mat ,  4UL );
      checkNonZeros( mat ,  4UL );

      if( sm(0,0) != 4 || sm(0,1) != 2 ||
          sm(1,0) != 4 || sm(1,1) != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 4 2 )\n( 4 2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) != 0 || mat(0,1) != 0 || mat(0,2) != 0 || mat(0,3) != 0 ||
          mat(1,0) != 4 || mat(1,1) != 2 || mat(1,2) != 0 || mat(1,3) != 0 ||
          mat(2,0) != 4 || mat(2,1) != 2 || mat(2,2) != 0 || mat(2,3) != 0 ||
          mat(3,0) != 0 || mat(3,1) != 0 || mat(3,2) != 0 || mat(3,3) != 0 ||
          mat(4,0) != 0 || mat(4,1) != 0 || mat(4,2) != 0 || mat(4,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 4  2  0  0 )\n"
                                     "( 4  2  0  0 )\n"
                                     "( 0  0  0  0 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major SparseSubmatrix multiplication assignment (aliasing)";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 2UL );
      sm *= submatrix( mat_, 2UL, 1UL, 2UL, 2UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  3UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) != 4 || sm(0,1) != 5 ||
          sm(1,0) != 0 || sm(1,1) != 6 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 4  5 )\n( 0  6 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 4 || mat_(1,1) !=  5 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 0 || mat_(2,1) !=  6 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n( 0  0  0  0 )\n"
                                     "( 4  5  0  0 )\n"
                                     "( 0  6 -3  0 )\n"
                                     "( 0  4  5 -6 )\n"
                                     "( 7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major dense matrix multiplication assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 2UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 0 );
      mat(0,0) = -11;
      mat(0,1) = -12;
      mat(1,0) =  13;
      mat(1,1) =  14;

      sm *= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( sm(0,0) != 13 || sm(0,1) != 14 ||
          sm(1,0) != 22 || sm(1,1) != 24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 13 14 )\n( 22 24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 13 || mat_(1,1) != 14 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 22 || mat_(2,1) != 24 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( 13 14  0  0 )\n"
                                     "( 22 24 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major dense matrix multiplication assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 2UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 0 );
      mat(0,0) = -11;
      mat(0,1) = -12;
      mat(1,0) =  13;
      mat(1,1) =  14;

      sm *= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( sm(0,0) != 13 || sm(0,1) != 14 ||
          sm(1,0) != 22 || sm(1,1) != 24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 13 14 )\n( 22 24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 13 || mat_(1,1) != 14 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 22 || mat_(2,1) != 24 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( 13 14  0  0 )\n"
                                     "( 22 24 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Row-major/row-major sparse matrix multiplication assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 2UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) = -11;
      mat(0,1) = -12;
      mat(1,0) =  13;
      mat(1,1) =  14;

      sm *= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( sm(0,0) != 13 || sm(0,1) != 14 ||
          sm(1,0) != 22 || sm(1,1) != 24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 13 14 )\n( 22 24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 13 || mat_(1,1) != 14 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 22 || mat_(2,1) != 24 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( 13 14  0  0 )\n"
                                     "( 22 24 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major/column-major sparse matrix multiplication assignment";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 2UL, 2UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) = -11;
      mat(0,1) = -12;
      mat(1,0) =  13;
      mat(1,1) =  14;

      sm *= mat;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( sm(0,0) != 13 || sm(0,1) != 14 ||
          sm(1,0) != 22 || sm(1,1) != 24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 13 14 )\n( 22 24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 13 || mat_(1,1) != 14 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 22 || mat_(2,1) != 24 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "( 13 14  0  0 )\n"
                                     "( 22 24 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major SparseSubmatrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix multiplication assignment (no aliasing)";

      initialize();

      OMT mat( 4UL, 5UL, 4UL );
      mat(0,1) = 1;
      mat(0,2) = 1;
      mat(1,1) = 1;
      mat(1,2) = 1;

      OSMT sm = submatrix( mat, 0UL, 1UL, 2UL, 2UL );
      sm *= submatrix( tmat_, 1UL, 2UL, 2UL, 2UL );

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );
      checkRows    ( mat  ,  4UL );
      checkColumns ( mat  ,  5UL );
      checkNonZeros( mat  ,  4UL );

      if( sm(0,0) != -3 || sm(0,1) != 9 ||
          sm(1,0) != -3 || sm(1,1) != 9 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -3 -3 )\n(  9  9 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat(0,0) != 0 || mat(0,1) != -3 || mat(0,2) != 9 || mat(0,3) != 0 || mat(0,4) != 0 ||
          mat(1,0) != 0 || mat(1,1) != -3 || mat(1,2) != 9 || mat(1,3) != 0 || mat(1,4) != 0 ||
          mat(2,0) != 0 || mat(2,1) !=  0 || mat(2,2) != 0 || mat(2,3) != 0 || mat(2,4) != 0 ||
          mat(3,0) != 0 || mat(3,1) !=  0 || mat(3,2) != 0 || mat(3,3) != 0 || mat(3,4) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << mat << "\n"
             << "   Expected result:\n( 0 -3  9  0  0 )\n"
                                     "( 0 -3  9  0  0 )\n"
                                     "( 0  0  0  0  0 )\n"
                                     "( 0  0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major SparseSubmatrix multiplication assignment (aliasing)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 2UL );
      sm *= submatrix( tmat_, 1UL, 2UL, 2UL, 2UL );

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  3UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) != 6 || sm(0,1) != -10 ||
          sm(1,0) != 0 || sm(1,1) !=   4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 6 -10 )\n( 0   4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 6 || tmat_(0,2) != -10 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 0 || tmat_(1,2) !=   4 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) !=  -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=   0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  6 -10  0  7 )\n"
                                     "( 0  0   4  4 -8 )\n"
                                     "( 0  0  -3  5  9 )\n"
                                     "( 0  0   0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major dense matrix multiplication assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 2UL );

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 0 );
      mat(0,0) =  11;
      mat(0,1) =  12;
      mat(1,0) = -13;
      mat(1,1) = -14;

      sm *= mat;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 12UL );

      if( sm(0,0) != 26 || sm(0,1) != 28 ||
          sm(1,0) != 11 || sm(1,1) != 12 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 26 28 )\n( 11 12 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 26 || tmat_(0,2) != 28 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 12 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0 26 28  0  7 )\n"
                                     "( 0 11 12  4 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major dense matrix multiplication assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 2UL );

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 0 );
      mat(0,0) =  11;
      mat(0,1) =  12;
      mat(1,0) = -13;
      mat(1,1) = -14;

      sm *= mat;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 12UL );

      if( sm(0,0) != 26 || sm(0,1) != 28 ||
          sm(1,0) != 11 || sm(1,1) != 12 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 26 28 )\n( 11 12 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 26 || tmat_(0,2) != 28 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 12 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0 26 28  0  7 )\n"
                                     "( 0 11 12  4 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix multiplication assignment
   //=====================================================================================

   {
      test_ = "Column-major/row-major sparse matrix multiplication assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 2UL );

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) =  11;
      mat(0,1) =  12;
      mat(1,0) = -13;
      mat(1,1) = -14;

      sm *= mat;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 12UL );

      if( sm(0,0) != 26 || sm(0,1) != 28 ||
          sm(1,0) != 11 || sm(1,1) != 12 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 26 28 )\n( 11 12 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 26 || tmat_(0,2) != 28 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 12 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0 26 28  0  7 )\n"
                                     "( 0 11 12  4 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major/column-major sparse matrix multiplication assignment";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 2UL );

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) =  11;
      mat(0,1) =  12;
      mat(1,0) = -13;
      mat(1,1) = -14;

      sm *= mat;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 12UL );

      if( sm(0,0) != 26 || sm(0,1) != 28 ||
          sm(1,0) != 11 || sm(1,1) != 12 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 26 28 )\n( 11 12 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 26 || tmat_(0,2) != 28 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 11 || tmat_(1,2) != 12 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0 26 28  0  7 )\n"
                                     "( 0 11 12  4 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of all SparseSubmatrix (self-)scaling operations.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all available ways to scale an instance of the SparseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testScaling()
{
   //=====================================================================================
   // Row-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M*=s) (2x3)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 2UL, 3UL );

      sm *= 3;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 || sm(0,2) != -9 ||
          sm(1,0) !=  0 || sm(1,1) != 12 || sm(1,2) != 15 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0 -9 )\n(  0 12 15 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=  0 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) != 12 || mat_(3,2) != 15 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0 12 15 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M*=s) (3x2)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 3UL, 2UL );

      sm *= 3;

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=   0 ||
          sm(1,0) !=  0 || sm(1,1) !=  12 ||
          sm(2,0) != 21 || sm(2,1) != -24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6   0 )\n(  0  12 )\n( 21 -24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=   0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=   1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=   0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  12 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 21 || mat_(4,1) != -24 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0   0  0  0 )\n"
                                     "(  0   1  0  0 )\n"
                                     "( -6   0 -3  0 )\n"
                                     "(  0  12  5 -6 )\n"
                                     "( 21 -24  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M*s) (2x3)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 2UL, 3UL );

      sm = sm * 3;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 || sm(0,2) != -9 ||
          sm(1,0) !=  0 || sm(1,1) != 12 || sm(1,2) != 15 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0 -9 )\n(  0 12 15 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=  0 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) != 12 || mat_(3,2) != 15 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0 12 15 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=M*s) (3x2)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 3UL, 2UL );

      sm = sm * 3;

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=   0 ||
          sm(1,0) !=  0 || sm(1,1) !=  12 ||
          sm(2,0) != 21 || sm(2,1) != -24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6   0 )\n(  0  12 )\n( 21 -24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=   0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=   1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=   0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  12 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 21 || mat_(4,1) != -24 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0   0  0  0 )\n"
                                     "(  0   1  0  0 )\n"
                                     "( -6   0 -3  0 )\n"
                                     "(  0  12  5 -6 )\n"
                                     "( 21 -24  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=s*M) (2x3)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 2UL, 3UL );

      sm = 3 * sm;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 || sm(0,2) != -9 ||
          sm(1,0) !=  0 || sm(1,1) != 12 || sm(1,2) != 15 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0 -9 )\n(  0 12 15 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=  0 || mat_(2,2) != -9 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) != 12 || mat_(3,2) != 15 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -6  0 -9  0 )\n"
                                     "(  0 12 15 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=s*M) (3x2)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 3UL, 2UL );

      sm = 3 * sm;

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=   0 ||
          sm(1,0) !=  0 || sm(1,1) !=  12 ||
          sm(2,0) != 21 || sm(2,1) != -24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6   0 )\n(  0  12 )\n( 21 -24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=   0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=   1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -6 || mat_(2,1) !=   0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  12 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 21 || mat_(4,1) != -24 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0   0  0  0 )\n"
                                     "(  0   1  0  0 )\n"
                                     "( -6   0 -3  0 )\n"
                                     "(  0  12  5 -6 )\n"
                                     "( 21 -24  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M/=s) (2x3)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 2UL, 3UL );

      sm /= 0.5;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -4 || sm(0,1) != 0 || sm(0,2) != -6 ||
          sm(1,0) !=  0 || sm(1,1) != 8 || sm(1,2) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4  0 -6 )\n(  0  8 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != -6 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  8 || mat_(3,2) != 10 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0 -6  0 )\n"
                                     "(  0  8 10 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M/=s) (3x2)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 3UL, 2UL );

      sm /= 0.5;

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -4 || sm(0,1) !=   0 ||
          sm(1,0) !=  0 || sm(1,1) !=   8 ||
          sm(2,0) != 14 || sm(2,1) != -16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4   0 )\n(  0   8 )\n( 14 -16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=   0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=   1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=   0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=   8 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 14 || mat_(4,1) != -16 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0   0  0  0 )\n"
                                     "(  0   1  0  0 )\n"
                                     "( -4   0 -3  0 )\n"
                                     "(  0   8  5 -6 )\n"
                                     "( 14 -16  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M/s) (2x3)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 2UL, 3UL );

      sm = sm / 0.5;

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -4 || sm(0,1) != 0 || sm(0,2) != -6 ||
          sm(1,0) !=  0 || sm(1,1) != 8 || sm(1,2) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4  0 -6 )\n(  0  8 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=  0 || mat_(2,2) != -6 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  8 || mat_(3,2) != 10 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  1  0  0 )\n"
                                     "( -4  0 -6  0 )\n"
                                     "(  0  8 10 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-scaling (M=M/s) (3x2)";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 0UL, 3UL, 2UL );

      sm = sm / 0.5;

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  2UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != -4 || sm(0,1) !=   0 ||
          sm(1,0) !=  0 || sm(1,1) !=   8 ||
          sm(2,0) != 14 || sm(2,1) != -16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4   0 )\n(  0   8 )\n( 14 -16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=   0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=   1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -4 || mat_(2,1) !=   0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=   8 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) != 14 || mat_(4,1) != -16 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0   0  0  0 )\n"
                                     "(  0   1  0  0 )\n"
                                     "( -4   0 -3  0 )\n"
                                     "(  0   8  5 -6 )\n"
                                     "( 14 -16  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major SparseSubmatrix::scale()
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::scale()";

      initialize();

      // Initialization check
      SMT sm = submatrix( mat_, 2UL, 1UL, 2UL, 2UL );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 3UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 2UL );

      if( sm(0,0) != 0 || sm(0,1) != -3 ||
          sm(1,0) != 4 || sm(1,1) !=  5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -3 )\n( 4  5 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the matrix
      sm.scale( 2 );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 3UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 2UL );

      if( sm(0,0) != 0 || sm(0,1) != -6 ||
          sm(1,0) != 8 || sm(1,1) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Integral scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -6 )\n( 8 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      sm.scale( 0.5 );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 3UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 2UL );

      if( sm(0,0) != 0 || sm(0,1) != -3 ||
          sm(1,0) != 4 || sm(1,1) !=  5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Floating point scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -3 )\n( 4  5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M*=s) (3x2)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 3UL, 2UL );

      sm *= 3;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 ||
          sm(1,0) !=  0 || sm(1,1) != 12 ||
          sm(2,0) != -9 || sm(2,1) != 15 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0 )\n(  0 12 )\n( -9 15 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) != 12 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -9 || tmat_(2,3) != 15 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  7 )\n"
                                     "( 0  1  0 12 -8 )\n"
                                     "( 0  0 -9 15  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-scaling (M*=s) (2x3)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 2UL, 3UL );

      sm *= 3;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  3UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 || sm(0,2) !=  21 ||
          sm(1,0) !=  0 || sm(1,1) != 12 || sm(1,2) != -24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0  21 )\n(  0 12 -24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  21 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) != 12 || tmat_(1,4) != -24 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=   9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) !=  10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  21 )\n"
                                     "( 0  1  0 12 -24 )\n"
                                     "( 0  0 -3  5   9 )\n"
                                     "( 0  0  0 -6  10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=M*s) (3x2)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 3UL, 2UL );

      sm = sm * 3;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 ||
          sm(1,0) !=  0 || sm(1,1) != 12 ||
          sm(2,0) != -9 || sm(2,1) != 15 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0 )\n(  0 12 )\n( -9 15 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) != 12 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -9 || tmat_(2,3) != 15 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  7 )\n"
                                     "( 0  1  0 12 -8 )\n"
                                     "( 0  0 -9 15  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-scaling (M=M*s) (2x3)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 2UL, 3UL );

      sm = sm * 3;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  3UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 || sm(0,2) !=  21 ||
          sm(1,0) !=  0 || sm(1,1) != 12 || sm(1,2) != -24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0  21 )\n(  0 12 -24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  21 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) != 12 || tmat_(1,4) != -24 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=   9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) !=  10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  21 )\n"
                                     "( 0  1  0 12 -24 )\n"
                                     "( 0  0 -3  5   9 )\n"
                                     "( 0  0  0 -6  10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=s*M) (3x2)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 3UL, 2UL );

      sm = 3 * sm;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 ||
          sm(1,0) !=  0 || sm(1,1) != 12 ||
          sm(2,0) != -9 || sm(2,1) != 15 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0 )\n(  0 12 )\n( -9 15 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) != 12 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -9 || tmat_(2,3) != 15 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  7 )\n"
                                     "( 0  1  0 12 -8 )\n"
                                     "( 0  0 -9 15  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-scaling (M=s*M) (2x3)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 2UL, 3UL );

      sm = 3 * sm;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  3UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -6 || sm(0,1) !=  0 || sm(0,2) !=  21 ||
          sm(1,0) !=  0 || sm(1,1) != 12 || sm(1,2) != -24 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -6  0  21 )\n(  0 12 -24 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -6 || tmat_(0,3) !=  0 || tmat_(0,4) !=  21 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) != 12 || tmat_(1,4) != -24 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=   9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) !=  10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -6  0  21 )\n"
                                     "( 0  1  0 12 -24 )\n"
                                     "( 0  0 -3  5   9 )\n"
                                     "( 0  0  0 -6  10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M/=s) (3x2)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 3UL, 2UL );

      sm /= 0.5;

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -4 || sm(0,1) !=  0 ||
          sm(1,0) !=  0 || sm(1,1) !=  8 ||
          sm(2,0) != -6 || sm(2,1) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4  0 )\n(  0  8 )\n( -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -4 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  8 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -6 || tmat_(2,3) != 10 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -4  0  7 )\n"
                                     "( 0  1  0  8 -8 )\n"
                                     "( 0  0 -6 10  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-scaling (M/=s) (2x3)";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 2UL, 2UL, 3UL );

      sm /= 0.5;

      checkRows    ( sm   ,  2UL );
      checkColumns ( sm   ,  3UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) != -4 || sm(0,1) != 0 || sm(0,2) !=  14 ||
          sm(1,0) !=  0 || sm(1,1) != 8 || sm(1,2) != -16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( -4  0  14 )\n(  0  8 -16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -4 || tmat_(0,3) !=  0 || tmat_(0,4) !=  14 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  8 || tmat_(1,4) != -16 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=   9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) !=  10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -4  0  14 )\n"
                                     "( 0  1  0  8 -16 )\n"
                                     "( 0  0 -3  5   9 )\n"
                                     "( 0  0  0 -6  10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major SparseSubmatrix::scale()
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::scale()";

      initialize();

      // Initialization check
      OSMT sm = submatrix( tmat_, 1UL, 2UL, 2UL, 2UL );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 3UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 2UL );

      if( sm(0,0) !=  0 || sm(0,1) != 4 ||
          sm(1,0) != -3 || sm(1,1) != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 4 )\n( -3 5 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the matrix
      sm.scale( 2 );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 3UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 2UL );

      if( sm(0,0) !=  0 || sm(0,1) !=  8 ||
          sm(1,0) != -6 || sm(1,1) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Integral scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  8 )\n( -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      sm.scale( 0.5 );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 3UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 2UL );

      if( sm(0,0) !=  0 || sm(0,1) != 4 ||
          sm(1,0) != -3 || sm(1,1) != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Floating point scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 4 )\n( -3 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix function call operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the function call operator
// of the SparseSubmatrix class template. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void ClassTest::testFunctionCall()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::operator()";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 1UL, 3UL, 2UL );

      // Assignment to the element (1,0)
      {
         sm(1,0) = 9;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  5UL );
         checkNonZeros( sm  ,  0UL, 1UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 2UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 11UL );

         if( sm(0,0) != 1 || sm(0,1) !=  0 ||
             sm(1,0) != 9 || sm(1,1) != -3 ||
             sm(2,0) != 4 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 1  0 )\n( 9 -3 )\n( 4  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  9 -3  0 )\n"
                                        "(  0  4  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (2,0)
      {
         sm(2,0) = 0;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  4UL );
         checkNonZeros( sm  ,  0UL, 1UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 1UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 10UL );

         if( sm(0,0) != 1 || sm(0,1) !=  0 ||
             sm(1,0) != 9 || sm(1,1) != -3 ||
             sm(2,0) != 0 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 1  0 )\n( 9 -3 )\n( 0  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  9 -3  0 )\n"
                                        "(  0  0  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (1,1)
      {
         sm(1,1) = 11;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  4UL );
         checkNonZeros( sm  ,  0UL, 1UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 1UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 10UL );

         if( sm(0,0) != 1 || sm(0,1) !=  0 ||
             sm(1,0) != 9 || sm(1,1) != 11 ||
             sm(2,0) != 0 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 1  0 )\n( 9 11 )\n( 0  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  9 11  0 )\n"
                                        "(  0  0  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Addition assignment to the element (0,0)
      {
         sm(0,0) += 3;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  4UL );
         checkNonZeros( sm  ,  0UL, 1UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 1UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 10UL );

         if( sm(0,0) != 4 || sm(0,1) !=  0 ||
             sm(1,0) != 9 || sm(1,1) != 11 ||
             sm(2,0) != 0 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4  0 )\n( 9 11 )\n( 0  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  4 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  4  0  0 )\n"
                                        "( -2  9 11  0 )\n"
                                        "(  0  0  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Subtraction assignment to the element (0,1)
      {
         sm(0,1) -= 6;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  5UL );
         checkNonZeros( sm  ,  0UL, 2UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 1UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 11UL );

         if( sm(0,0) != 4 || sm(0,1) != -6 ||
             sm(1,0) != 9 || sm(1,1) != 11 ||
             sm(2,0) != 0 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4 -6 )\n( 9 11 )\n( 0  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  4 || mat_(1,2) != -6 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  4 -6  0 )\n"
                                        "( -2  9 11  0 )\n"
                                        "(  0  0  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Multiplication assignment to the element (1,1)
      {
         sm(1,1) *= 2;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  5UL );
         checkNonZeros( sm  ,  0UL, 2UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 1UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 11UL );

         if( sm(0,0) != 4 || sm(0,1) != -6 ||
             sm(1,0) != 9 || sm(1,1) != 22 ||
             sm(2,0) != 0 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4 -6 )\n( 9 22 )\n( 0  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  4 || mat_(1,2) != -6 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 22 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  4 -6  0 )\n"
                                        "( -2  9 22  0 )\n"
                                        "(  0  0  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Division assignment to the element (1,1)
      {
         sm(1,1) /= 2;

         checkRows    ( sm  ,  3UL );
         checkColumns ( sm  ,  2UL );
         checkNonZeros( sm  ,  5UL );
         checkNonZeros( sm  ,  0UL, 2UL );
         checkNonZeros( sm  ,  1UL, 2UL );
         checkNonZeros( sm  ,  2UL, 1UL );
         checkRows    ( mat_,  5UL );
         checkColumns ( mat_,  4UL );
         checkNonZeros( mat_, 11UL );

         if( sm(0,0) != 4 || sm(0,1) != -6 ||
             sm(1,0) != 9 || sm(1,1) != 11 ||
             sm(2,0) != 0 || sm(2,1) !=  5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4 -6 )\n( 9 11 )\n( 0  5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  4 || mat_(1,2) != -6 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  9 || mat_(2,2) != 11 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  4 -6  0 )\n"
                                        "( -2  9 11  0 )\n"
                                        "(  0  0  5 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::operator()";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );

      // Assignment to the element (0,1)
      {
         sm(0,1) = 9;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  5UL );
         checkNonZeros( sm   ,  0UL, 1UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 2UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 11UL );

         if( sm(0,0) != 1 || sm(0,1) !=  9 || sm(0,2) != 4 ||
             sm(1,0) != 0 || sm(1,1) != -3 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 1  9 4 )\n( 0 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  9 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  1  9  4 -8 )\n"
                                        "( 0  0 -3  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (0,2)
      {
         sm(0,2) = 0;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  4UL );
         checkNonZeros( sm   ,  0UL, 1UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 1UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 10UL );

         if( sm(0,0) != 1 || sm(0,1) !=  9 || sm(0,2) != 0 ||
             sm(1,0) != 0 || sm(1,1) != -3 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 1  9 0 )\n( 0 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  9 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  1  9  0 -8 )\n"
                                        "( 0  0 -3  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Assignment to the element (1,1)
      {
         sm(1,1) = 11;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  4UL );
         checkNonZeros( sm   ,  0UL, 1UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 1UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 10UL );

         if( sm(0,0) != 1 || sm(0,1) !=  9 || sm(0,2) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 11 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 1 11 0 )\n( 0 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) != 1 || tmat_(1,2) !=  9 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  1  9  0 -8 )\n"
                                        "( 0  0 11  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Addition assignment to the element (0,0)
      {
         sm(0,0) += 3;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  4UL );
         checkNonZeros( sm   ,  0UL, 1UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 1UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 10UL );

         if( sm(0,0) != 4 || sm(0,1) !=  9 || sm(0,2) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 11 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4 11 0 )\n( 0 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) != 4 || tmat_(1,2) !=  9 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  4  9  0 -8 )\n"
                                        "( 0  0 11  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Subtraction assignment to the element (1,0)
      {
         sm(1,0) -= 6;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  5UL );
         checkNonZeros( sm   ,  0UL, 2UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 1UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 11UL );

         if( sm(0,0) !=  4 || sm(0,1) !=  9 || sm(0,2) != 0 ||
             sm(1,0) != -6 || sm(1,1) != 11 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 11 0 )\n( -6 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  4 || tmat_(1,2) !=  9 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != -6 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  4  9  0 -8 )\n"
                                        "( 0 -6 11  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Multiplication assignment to the element (1,1)
      {
         sm(1,1) *= 2;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  5UL );
         checkNonZeros( sm   ,  0UL, 2UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 1UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 11UL );

         if( sm(0,0) !=  4 || sm(0,1) !=  9 || sm(0,2) != 0 ||
             sm(1,0) != -6 || sm(1,1) != 22 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 22 0 )\n( -6 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  4 || tmat_(1,2) !=  9 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != -6 || tmat_(2,2) != 22 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  4  9  0 -8 )\n"
                                        "( 0 -6 22  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Division assignment to the element (1,1)
      {
         sm(1,1) /= 2;

         checkRows    ( sm   ,  2UL );
         checkColumns ( sm   ,  3UL );
         checkNonZeros( sm   ,  5UL );
         checkNonZeros( sm   ,  0UL, 2UL );
         checkNonZeros( sm   ,  1UL, 2UL );
         checkNonZeros( sm   ,  2UL, 1UL );
         checkRows    ( tmat_,  4UL );
         checkColumns ( tmat_,  5UL );
         checkNonZeros( tmat_, 11UL );

         if( sm(0,0) !=  4 || sm(0,1) !=  9 || sm(0,2) != 0 ||
             sm(1,0) != -6 || sm(1,1) != 11 || sm(1,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 11 0 )\n( -6 -3 5 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  4 || tmat_(1,2) !=  9 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) != -6 || tmat_(2,2) != 11 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subscript operator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  4  9  0 -8 )\n"
                                        "( 0 -6 11  5  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the SparseSubmatrix iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIterator()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 3UL );

      // Testing the Iterator default constructor
      {
         test_ = "Row-major Iterator default constructor";

         SMT::Iterator it = SMT::Iterator();

         if( it != SMT::Iterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing the ConstIterator default constructor
      {
         test_ = "Row-major ConstIterator default constructor";

         SMT::ConstIterator it = SMT::ConstIterator();

         if( it != SMT::ConstIterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Row-major Iterator/ConstIterator conversion";

         SMT::ConstIterator it( begin( sm, 1UL ) );

         if( it == end( sm, 1UL ) || it->value() != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th row via Iterator
      {
         test_ = "Row-major Iterator subtraction";

         const size_t number( end( sm, 0UL ) - begin( sm, 0UL ) );

         if( number != 1UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 1\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via ConstIterator
      {
         test_ = "Row-major ConstIterator subtraction";

         const size_t number( cend( sm, 1UL ) - cbegin( sm, 1UL ) );

         if( number != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Row-major read-only access via ConstIterator";

         SMT::ConstIterator it ( cbegin( sm, 2UL ) );
         SMT::ConstIterator end( cend( sm, 2UL ) );

         if( it == end || it->value() != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || it->value() != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it != cend( sm, 2UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment via Iterator
      {
         test_ = "Row-major assignment via Iterator";

         int value = 8;

         for( SMT::Iterator it=begin( sm, 2UL ); it!=end( sm, 2UL ); ++it ) {
            *it = value++;
         }

         if( sm(0,0) !=  0 || sm(0,1) != 1 || sm(0,2) !=  0 ||
             sm(1,0) != -2 || sm(1,1) != 0 || sm(1,2) != -3 ||
             sm(2,0) !=  0 || sm(2,1) != 8 || sm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  0  1  0 )\n( -2  0 -3 )\n(  0  8  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  8 || mat_(3,2) !=  9 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  8  9 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Row-major addition assignment via Iterator";

         int value = 4;

         for( SMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it += value++;
         }

         if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 0 ||
             sm(1,0) != 2 || sm(1,1) != 0 || sm(1,2) != 2 ||
             sm(2,0) != 0 || sm(2,1) != 8 || sm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 1 0 )\n( 2 0 2 )\n( 0 8 9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
             mat_(1,0) != 0 || mat_(1,1) !=  1 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
             mat_(2,0) != 2 || mat_(2,1) !=  0 || mat_(2,2) != 2 || mat_(2,3) !=  0 ||
             mat_(3,0) != 0 || mat_(3,1) !=  8 || mat_(3,2) != 9 || mat_(3,3) != -6 ||
             mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "(  2  0  2  0 )\n"
                                        "(  0  8  9 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Row-major subtraction assignment via Iterator";

         int value = 4;

         for( SMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it -= value++;
         }

         if( sm(0,0) !=  0 || sm(0,1) != 1 || sm(0,2) !=  0 ||
             sm(1,0) != -2 || sm(1,1) != 0 || sm(1,2) != -3 ||
             sm(2,0) !=  0 || sm(2,1) != 8 || sm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  0  1  0 )\n( -2  0 -3 )\n(  0  8  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  8 || mat_(3,2) !=  9 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -3  0 )\n"
                                        "(  0  8  9 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Row-major multiplication assignment via Iterator";

         int value = 1;

         for( SMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it *= value++;
         }

         if( sm(0,0) !=  0 || sm(0,1) != 1 || sm(0,2) !=  0 ||
             sm(1,0) != -2 || sm(1,1) != 0 || sm(1,2) != -6 ||
             sm(2,0) !=  0 || sm(2,1) != 8 || sm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  0  1  0 )\n( -2  0 -6 )\n(  0  8  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -6 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  8 || mat_(3,2) !=  9 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -2  0 -6  0 )\n"
                                        "(  0  8  9 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Row-major division assignment via Iterator";

         for( SMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it /= 2;
         }

         if( sm(0,0) !=  0 || sm(0,1) != 1 || sm(0,2) !=  0 ||
             sm(1,0) != -1 || sm(1,1) != 0 || sm(1,2) != -3 ||
             sm(2,0) !=  0 || sm(2,1) != 8 || sm(2,2) !=  9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  0  1  0 )\n( -1  0 -3 )\n(  0  8  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
             mat_(1,0) !=  0 || mat_(1,1) !=  1 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
             mat_(2,0) != -1 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
             mat_(3,0) !=  0 || mat_(3,1) !=  8 || mat_(3,2) !=  9 || mat_(3,3) != -6 ||
             mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << mat_ << "\n"
                << "   Expected result:\n(  0  0  0  0 )\n"
                                        "(  0  1  0  0 )\n"
                                        "( -1  0 -3  0 )\n"
                                        "(  0  8  9 -6 )\n"
                                        "(  7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 3UL );

      // Testing the Iterator default constructor
      {
         test_ = "Row-major Iterator default constructor";

         OSMT::Iterator it = OSMT::Iterator();

         if( it != OSMT::Iterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing the ConstIterator default constructor
      {
         test_ = "Row-major ConstIterator default constructor";

         OSMT::ConstIterator it = OSMT::ConstIterator();

         if( it != OSMT::ConstIterator() ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator default constructor\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Column-major Iterator/ConstIterator conversion";

         OSMT::ConstIterator it( begin( sm, 1UL ) );

         if( it == end( sm, 1UL ) || it->value() != -2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th column via Iterator
      {
         test_ = "Column-major Iterator subtraction";

         const size_t number( end( sm, 0UL ) - begin( sm, 0UL ) );

         if( number != 1UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 1\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via ConstIterator
      {
         test_ = "Column-major ConstIterator subtraction";

         const size_t number( cend( sm, 1UL ) - cbegin( sm, 1UL ) );

         if( number != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Column-major read-only access via ConstIterator";

         OSMT::ConstIterator it ( cbegin( sm, 2UL ) );
         OSMT::ConstIterator end( cend( sm, 2UL ) );

         if( it == end || it->value() != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || it->value() != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it != cend( sm, 2UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment via Iterator
      {
         test_ = "Column-major assignment via Iterator";

         int value = 8;

         for( OSMT::Iterator it=begin( sm, 2UL ); it!=end( sm, 2UL ); ++it ) {
            *it = value++;
         }

         if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) != 0 ||
             sm(1,0) != 1 || sm(1,1) !=  0 || sm(1,2) != 8 ||
             sm(2,0) != 0 || sm(2,1) != -3 || sm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 -2  0 )\n( 1  0  8 )\n( 0 -3  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  8 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  9 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  1  0  8 -8 )\n"
                                        "( 0  0 -3  9  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment via Iterator
      {
         test_ = "Column-major addition assignment via Iterator";

         int value = 4;

         for( OSMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it += value++;
         }

         if( sm(0,0) != 0 || sm(0,1) != 2 || sm(0,2) != 0 ||
             sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 8 ||
             sm(2,0) != 0 || sm(2,1) != 2 || sm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 2 0 )\n( 1 0 8 )\n( 0 2 9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) != 0 || tmat_(1,3) !=  8 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 2 || tmat_(2,3) !=  9 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) != 0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Addition assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0  2  0  7 )\n"
                                        "( 0  1  0  8 -8 )\n"
                                        "( 0  0  2  9  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment via Iterator
      {
         test_ = "Column-major subtraction assignment via Iterator";

         int value = 4;

         for( OSMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it -= value++;
         }

         if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) != 0 ||
             sm(1,0) != 1 || sm(1,1) !=  0 || sm(1,2) != 8 ||
             sm(2,0) != 0 || sm(2,1) != -3 || sm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 -2  0 )\n( 1  0  8 )\n( 0 -3  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  8 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  9 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Subtraction assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  1  0  8 -8 )\n"
                                        "( 0  0 -3  9  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment via Iterator
      {
         test_ = "Column-major multiplication assignment via Iterator";

         int value = 1;

         for( OSMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it *= value++;
         }

         if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) != 0 ||
             sm(1,0) != 1 || sm(1,1) !=  0 || sm(1,2) != 8 ||
             sm(2,0) != 0 || sm(2,1) != -6 || sm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 -2  0 )\n( 1  0  8 )\n( 0 -6  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  8 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -6 || tmat_(2,3) !=  9 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Multiplication assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                        "( 0  1  0  8 -8 )\n"
                                        "( 0  0 -6  9  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment via Iterator
      {
         test_ = "Column-major division assignment via Iterator";

         for( OSMT::Iterator it=begin( sm, 1UL ); it!=end( sm, 1UL ); ++it ) {
            *it /= 2;
         }

         if( sm(0,0) != 0 || sm(0,1) != -1 || sm(0,2) != 0 ||
             sm(1,0) != 1 || sm(1,1) !=  0 || sm(1,2) != 8 ||
             sm(2,0) != 0 || sm(2,1) != -3 || sm(2,2) != 9 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 -1  0 )\n( 1  0  8 )\n( 0 -3  9 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != -1 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
             tmat_(1,0) != 0 || tmat_(1,1) !=  1 || tmat_(1,2) !=  0 || tmat_(1,3) !=  8 || tmat_(1,4) != -8 ||
             tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != -3 || tmat_(2,3) !=  9 || tmat_(2,4) !=  9 ||
             tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Division assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << tmat_ << "\n"
                << "   Expected result:\n( 0  0 -1  0  7 )\n"
                                        "( 0  1  0  8 -8 )\n"
                                        "( 0  0 -3  9  9 )\n"
                                        "( 0  0  0 -6 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c nonZeros() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c nonZeros() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testNonZeros()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::nonZeros()";

      initialize();

      // Initialization check
      SMT sm = submatrix( mat_, 1UL, 1UL, 2UL, 3UL );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 3UL );
      checkNonZeros( sm, 2UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 1UL );

      if( sm(0,0) != 1 || sm(0,1) !=  0 || sm(0,2) != 0 ||
          sm(1,0) != 0 || sm(1,1) != -3 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1  0 0 )\n( 0 -3 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the sparse submatrix
      sm(1,1) = 0;

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 3UL );
      checkNonZeros( sm, 1UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 0UL );

      if( sm(0,0) != 1 || sm(0,1) != 0 || sm(0,2) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the sparse matrix
      mat_(2,3) = 5;

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 3UL );
      checkNonZeros( sm, 2UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 1UL );

      if( sm(0,0) != 1 || sm(0,1) != 0 || sm(0,2) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 0 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::nonZeros()";

      initialize();

      // Initialization check
      OSMT sm = submatrix( tmat_, 1UL, 1UL, 3UL, 2UL );

      checkRows    ( sm, 3UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 2UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 1UL );

      if( sm(0,0) != 1 || sm(0,1) !=  0 ||
          sm(1,0) != 0 || sm(1,1) != -3 ||
          sm(2,0) != 0 || sm(2,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1  0 )\n( 0 -3 )\n( 0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the sparse submatrix
      sm(1,1) = 0;

      checkRows    ( sm, 3UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 1UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 0UL );

      if( sm(0,0) != 1 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ||
          sm(2,0) != 0 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Changing the number of non-zeros via the sparse matrix
      tmat_(3,2) = 5;

      checkRows    ( sm, 3UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 2UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 1UL );

      if( sm(0,0) != 1 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ||
          sm(2,0) != 0 || sm(2,1) != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 0 )\n( 0 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reset() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reset() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testReset()
{
   using blaze::reset;
   using blaze::isDefault;


   //=====================================================================================
   // Row-major single element reset
   //=====================================================================================

   {
      test_ = "Row-major reset() function";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 2UL );

      reset( sm(0,1) );

      checkRows    ( sm  , 3UL );
      checkColumns ( sm  , 2UL );
      checkNonZeros( sm  , 2UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( !isDefault( sm(0,1) ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 0 )\n( -2 0 )\n(  0 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  0 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  0  0  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major reset
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::reset()";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 2UL );

      reset( sm );

      checkRows    ( sm  , 3UL );
      checkColumns ( sm  , 2UL );
      checkNonZeros( sm  , 0UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 7UL );

      if( !isDefault( sm ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  0 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) !=  0 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  0 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  0  0  0 )\n"
                                     "(  0  0 -3  0 )\n"
                                     "(  0  0  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major row-wise reset
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::reset( size_t )";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 2UL );

      // Resetting the 0th row
      {
         reset( sm, 0UL );

         checkRows    ( sm  , 3UL );
         checkColumns ( sm  , 2UL );
         checkNonZeros( sm  , 2UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 9UL );

         if( sm(0,0) !=  0 || sm(0,1) != 0 ||
             sm(1,0) != -2 || sm(1,1) != 0 ||
             sm(2,0) !=  0 || sm(2,1) != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 0th row failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  0 0 )\n( -2 0 )\n(  0 4 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Resetting the 1st row
      {
         reset( sm, 1UL );

         checkRows    ( sm  , 3UL );
         checkColumns ( sm  , 2UL );
         checkNonZeros( sm  , 1UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 8UL );

         if( sm(0,0) != 0 || sm(0,1) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 ||
             sm(2,0) != 0 || sm(2,1) != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 1st row failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 )\n( 0 0 )\n( 0 4 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Resetting the 2nd row
      {
         reset( sm, 2UL );

         checkRows    ( sm  , 3UL );
         checkColumns ( sm  , 2UL );
         checkNonZeros( sm  , 0UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 7UL );

         if( sm(0,0) != 0 || sm(0,1) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 ||
             sm(2,0) != 0 || sm(2,1) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 2nd row failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 )\n( 0 0 )\n( 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major single element reset
   //=====================================================================================

   {
      test_ = "Column-major reset() function";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 3UL );

      reset( sm(1,0) );

      checkRows    ( sm   , 2UL );
      checkColumns ( sm   , 3UL );
      checkNonZeros( sm   , 2UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 9UL );

      if( !isDefault( sm(1,0) ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -2 0 )\n( 0  0 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 0 || tmat_(1,2) !=  0 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                     "( 0  0  0  4 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major reset
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::reset()";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 3UL );

      reset( sm );

      checkRows    ( sm   , 2UL );
      checkColumns ( sm   , 3UL );
      checkNonZeros( sm   , 0UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 7UL );

      if( !isDefault( sm ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) !=  0 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 0 || tmat_(1,2) !=  0 || tmat_(1,3) !=  0 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0  0  0  7 )\n"
                                     "( 0  0  0  0 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major row-wise reset
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::reset( size_t )";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 3UL );

      // Resetting the 0th column
      {
         reset( sm, 0UL );

         checkRows    ( sm   , 2UL );
         checkColumns ( sm   , 3UL );
         checkNonZeros( sm   , 2UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 9UL );

         if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) != 0 ||
             sm(1,0) != 0 || sm(1,1) !=  0 || sm(1,2) != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 0th column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 -2  0 )\n( 0  0  4 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Resetting the 1st column
      {
         reset( sm, 1UL );

         checkRows    ( sm   , 2UL );
         checkColumns ( sm   , 3UL );
         checkNonZeros( sm   , 1UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 8UL );

         if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 1st column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 )\n( 0 0 4 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Resetting the 2nd column
      {
         reset( sm, 2UL );

         checkRows    ( sm   , 2UL );
         checkColumns ( sm   , 3UL );
         checkNonZeros( sm   , 0UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 7UL );

         if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Reset operation of 2nd column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c clear() function with the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c clear() function with the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testClear()
{
   using blaze::clear;
   using blaze::isDefault;


   //=====================================================================================
   // Row-major single element clear
   //=====================================================================================

   {
      test_ = "Row-major clear() function";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 2UL );

      clear( sm(0,1) );

      checkRows    ( sm  , 3UL );
      checkColumns ( sm  , 2UL );
      checkNonZeros( sm  , 2UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( !isDefault( sm(0,1) ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0 0 )\n( -2 0 )\n(  0 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) !=  0 || mat_(0,1) !=  0 || mat_(0,2) !=  0 || mat_(0,3) !=  0 ||
          mat_(1,0) !=  0 || mat_(1,1) !=  0 || mat_(1,2) !=  0 || mat_(1,3) !=  0 ||
          mat_(2,0) != -2 || mat_(2,1) !=  0 || mat_(2,2) != -3 || mat_(2,3) !=  0 ||
          mat_(3,0) !=  0 || mat_(3,1) !=  4 || mat_(3,2) !=  5 || mat_(3,3) != -6 ||
          mat_(4,0) !=  7 || mat_(4,1) != -8 || mat_(4,2) !=  9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0  0  0  0 )\n"
                                     "( -2  0 -3  0 )\n"
                                     "(  0  4  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major single element clear
   //=====================================================================================

   {
      test_ = "Column-major clear() function";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 2UL, 3UL );

      clear( sm(1,0) );

      checkRows    ( sm   , 2UL );
      checkColumns ( sm   , 3UL );
      checkNonZeros( sm   , 2UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 9UL );

      if( !isDefault( sm(1,0) ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -2 0 )\n( 0  0 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) != 0 || tmat_(0,2) != -2 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != 0 || tmat_(1,2) !=  0 || tmat_(1,3) !=  4 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) != 0 || tmat_(2,2) != -3 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) != 0 || tmat_(3,2) !=  0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n( 0  0 -2  0  7 )\n"
                                     "( 0  0  0  4 -8 )\n"
                                     "( 0  0 -3  5  9 )\n"
                                     "( 0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c set() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c set() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testSet()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::set()";

      initialize();

      SMT sm = submatrix( mat_, 0UL, 1UL, 2UL, 3UL );

      // Setting a non-zero element at the end of the 0th row
      sm.set( 0UL, 2UL, 1 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 1 ||
          sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 1 )\n( 1 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Setting a non-zero element at the beginning of the 0th row
      sm.set( 0UL, 0UL, 2 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  3UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( sm(0,0) != 2 || sm(0,1) != 0 || sm(0,2) != 1 ||
          sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 0 1 )\n( 1 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Setting a non-zero element at the center of the 0th row
      sm.set( 0UL, 1UL, 3 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 13UL );

      if( sm(0,0) != 2 || sm(0,1) != 3 || sm(0,2) != 1 ||
          sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 3 1 )\n( 1 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Setting an already existing element
      sm.set( 1UL, 0UL, 4 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 13UL );

      if( sm(0,0) != 2 || sm(0,1) != 3 || sm(0,2) != 1 ||
          sm(1,0) != 4 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 3 1 )\n( 4 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::set()";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 0UL, 3UL, 2UL );

      // Setting a non-zero element at the end of the 0th column
      sm.set( 2UL, 0UL, 1 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  2UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 ||
          sm(1,0) != 0 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 1 )\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Setting a non-zero element at the beginning of the 0th column
      sm.set( 0UL, 0UL, 2 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  3UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 12UL );

      if( sm(0,0) != 2 || sm(0,1) != 1 ||
          sm(1,0) != 0 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 1 )\n( 0 0 )\n( 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Setting a non-zero element at the center of the 0th column
      sm.set( 1UL, 0UL, 3 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 13UL );

      if( sm(0,0) != 2 || sm(0,1) != 1 ||
          sm(1,0) != 3 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 1 )\n( 3 0 )\n( 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Setting an already existing element
      sm.set( 0UL, 1UL, 4 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 13UL );

      if( sm(0,0) != 2 || sm(0,1) != 4 ||
          sm(1,0) != 3 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 4 )\n( 3 0 )\n( 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c insert() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c insert() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testInsert()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::insert()";

      initialize();

      SMT sm = submatrix( mat_, 0UL, 1UL, 2UL, 3UL );

      // Inserting a non-zero element at the end of the 0th row
      sm.insert( 0UL, 2UL, 1 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  2UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 11UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 1 ||
          sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 1 )\n( 1 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Inserting a non-zero element at the beginning of the 0th row
      sm.insert( 0UL, 0UL, 2 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  3UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 12UL );

      if( sm(0,0) != 2 || sm(0,1) != 0 || sm(0,2) != 1 ||
          sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 0 1 )\n( 1 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Inserting a non-zero element at the center of the 0th row
      sm.insert( 0UL, 1UL, 3 );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  4UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 13UL );

      if( sm(0,0) != 2 || sm(0,1) != 3 || sm(0,2) != 1 ||
          sm(1,0) != 1 || sm(1,1) != 0 || sm(1,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 3 1 )\n( 1 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to insert an already existing element
      try {
         sm.insert( 1UL, 0UL, 4 );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting an existing element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 3 1 )\n( 4 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::insert()";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 0UL, 3UL, 2UL );

      // Inserting a non-zero element at the end of the 0th column
      sm.insert( 2UL, 0UL, 1 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  2UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 11UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 ||
          sm(1,0) != 0 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 1 )\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Inserting a non-zero element at the beginning of the 0th column
      sm.insert( 0UL, 0UL, 2 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  3UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 12UL );

      if( sm(0,0) != 2 || sm(0,1) != 1 ||
          sm(1,0) != 0 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 1 )\n( 0 0 )\n( 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Inserting a non-zero element at the center of the 0th column
      sm.insert( 1UL, 0UL, 3 );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkNonZeros( sm   ,  4UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 13UL );

      if( sm(0,0) != 2 || sm(0,1) != 1 ||
          sm(1,0) != 3 || sm(1,1) != 0 ||
          sm(2,0) != 1 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 1 )\n( 3 0 )\n( 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to insert an already existing element
      try {
         sm.insert( 0UL, 1UL, 4 );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting an existing element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 2 4 )\n( 3 0 )\n( 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c append() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c append() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAppend()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::append()";

      // Appending with pre-allocation in each row
      {
         mat_.reset();

         // Initialization check
         SMT sm = submatrix( mat_, 0UL, 0UL, 4UL, 4UL );
         sm.reserve( 0UL, 2UL );
         sm.reserve( 2UL, 1UL );
         sm.reserve( 3UL, 2UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 0UL );
         checkNonZeros( sm, 0UL, 0UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 0UL );

         // Appending one non-zero element
         sm.append( 2UL, 1UL, 1 );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 1UL );
         checkNonZeros( sm, 0UL, 0UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 1UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(2,1) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n( 0 0 0 0 )\n( 0 1 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 0UL, 0UL, 2 );
         sm.append( 0UL, 3UL, 3 );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 3UL );
         checkNonZeros( sm, 0UL, 2UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 1UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(2,1) != 1 || sm(0,0) != 2 || sm(0,3) != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 2 0 0 3 )\n( 0 0 0 0 )\n( 0 1 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 3UL, 1UL, 4 );
         sm.append( 3UL, 2UL, 5 );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 5UL );
         checkNonZeros( sm, 0UL, 2UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 1UL );
         checkNonZeros( sm, 3UL, 2UL );

         if( sm(2,1) != 1 || sm(0,0) != 2 || sm(0,3) != 3 ||
             sm(3,1) != 4 || sm(3,2) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 2 0 0 3 )\n( 0 0 0 0 )\n( 0 1 0 0 )\n( 0 4 5 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Appending with row finalization
      {
         mat_.reset();

         // Initialization check
         SMT sm = submatrix( mat_, 0UL, 0UL, 4UL, 4UL );
         sm.reserve( 0UL, 2UL );
         sm.reserve( 2UL, 1UL );
         sm.reserve( 3UL, 2UL );

         // Appending one non-zero element
         sm.append( 0UL, 1UL, 1 );
         sm.finalize( 0UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 1UL );
         checkNonZeros( sm, 0UL, 1UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(0,1) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 1 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 1UL, 1UL, 2 );
         sm.append( 1UL, 3UL, 3 );
         sm.finalize( 1UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 3UL );
         checkNonZeros( sm, 0UL, 1UL );
         checkNonZeros( sm, 1UL, 2UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(0,1) != 1 || sm(1,1) != 2 || sm(1,3) != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 1 0 0 )\n( 0 2 0 3 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 3UL, 0UL, 4 );
         sm.append( 3UL, 1UL, 5 );
         sm.finalize( 1UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 5UL );
         checkNonZeros( sm, 0UL, 1UL );
         checkNonZeros( sm, 1UL, 2UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 2UL );

         if( sm(0,1) != 1 || sm(1,1) != 2 || sm(1,3) != 3 ||
             sm(3,0) != 4 || sm(3,1) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 1 0 0 )\n( 0 2 0 3 )\n( 0 0 0 0 )\n( 4 5 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::append()";

      // Appending with pre-allocation in each row
      {
         tmat_.reset();

         // Initialization check
         OSMT sm = submatrix( tmat_, 0UL, 0UL, 4UL, 4UL );
         sm.reserve( 0UL, 2UL );
         sm.reserve( 2UL, 1UL );
         sm.reserve( 3UL, 2UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 0UL );
         checkNonZeros( sm, 0UL, 0UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 0UL );

         // Appending one non-zero element
         sm.append( 1UL, 2UL, 1 );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 1UL );
         checkNonZeros( sm, 0UL, 0UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 1UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(1,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n( 0 0 1 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 0UL, 0UL, 2 );
         sm.append( 3UL, 0UL, 3 );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 3UL );
         checkNonZeros( sm, 0UL, 2UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 1UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(1,2) != 1 || sm(0,0) != 2 || sm(3,0) != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 2 0 0 0 )\n( 0 0 1 0 )\n( 0 0 0 0 )\n( 3 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 1UL, 3UL, 4 );
         sm.append( 2UL, 3UL, 5 );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 5UL );
         checkNonZeros( sm, 0UL, 2UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 1UL );
         checkNonZeros( sm, 3UL, 2UL );

         if( sm(1,2) != 1 || sm(0,0) != 2 || sm(3,0) != 3 ||
             sm(1,3) != 4 || sm(2,3) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 2 0 0 0 )\n( 0 0 1 4 )\n( 0 0 0 5 )\n( 3 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Appending with row finalization
      {
         tmat_.reset();

         // Initialization check
         OSMT sm = submatrix( tmat_, 0UL, 0UL, 4UL, 4UL );
         sm.reserve( 0UL, 2UL );
         sm.reserve( 2UL, 1UL );
         sm.reserve( 3UL, 2UL );

         // Appending one non-zero element
         sm.append( 1UL, 0UL, 1 );
         sm.finalize( 0UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 1UL );
         checkNonZeros( sm, 0UL, 1UL );
         checkNonZeros( sm, 1UL, 0UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(1,0) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n( 1 0 0 0 )\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 1UL, 1UL, 2 );
         sm.append( 3UL, 1UL, 3 );
         sm.finalize( 1UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 3UL );
         checkNonZeros( sm, 0UL, 1UL );
         checkNonZeros( sm, 1UL, 2UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 0UL );

         if( sm(1,0) != 1 || sm(1,1) != 2 || sm(3,1) != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n( 1 2 0 0 )\n( 0 0 0 0 )\n( 0 3 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         sm.append( 0UL, 3UL, 4 );
         sm.append( 1UL, 3UL, 5 );
         sm.finalize( 1UL );

         checkRows    ( sm, 4UL );
         checkColumns ( sm, 4UL );
         checkCapacity( sm, 5UL );
         checkNonZeros( sm, 5UL );
         checkNonZeros( sm, 0UL, 1UL );
         checkNonZeros( sm, 1UL, 2UL );
         checkNonZeros( sm, 2UL, 0UL );
         checkNonZeros( sm, 3UL, 2UL );

         if( sm(1,0) != 1 || sm(1,1) != 2 || sm(3,1) != 3 ||
             sm(0,3) != 4 || sm(1,3) != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 4 )\n( 1 2 0 5 )\n( 0 0 0 0 )\n( 0 3 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c erase() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c erase() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testErase()
{
   //=====================================================================================
   // Row-major index-based erase function
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::erase( size_t, size_t )";

      initialize();

      SMT sm = submatrix( mat_, 3UL, 1UL, 2UL, 3UL );

      // Erasing the non-zero element at the end of the 1st row
      sm.erase( 1UL, 2UL );

      checkRows    ( sm  , 2UL );
      checkColumns ( sm  , 3UL );
      checkNonZeros( sm  , 5UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 9UL );

      if( sm(0,0) !=  4 || sm(0,1) != 5 || sm(0,2) != -6 ||
          sm(1,0) != -8 || sm(1,1) != 9 || sm(1,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  4  5 -6 )\n( -8  9  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the non-zero element at the beginning of the 1st row
      sm.erase( 1UL, 0UL );

      checkRows    ( sm  , 2UL );
      checkColumns ( sm  , 3UL );
      checkNonZeros( sm  , 4UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 8UL );

      if( sm(0,0) != 4 || sm(0,1) != 5 || sm(0,2) != -6 ||
          sm(1,0) != 0 || sm(1,1) != 9 || sm(1,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 4  5 -6 )\n( 0  9  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the non-zero element at the beginning of the 1st row
      sm.erase( 1UL, 1UL );

      checkRows    ( sm  , 2UL );
      checkColumns ( sm  , 3UL );
      checkNonZeros( sm  , 3UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 7UL );

      if( sm(0,0) != 4 || sm(0,1) != 5 || sm(0,2) != -6 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 4  5 -6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase an already erased element
      sm.erase( 1UL, 2UL );

      checkRows    ( sm  , 2UL );
      checkColumns ( sm  , 3UL );
      checkNonZeros( sm  , 3UL );
      checkRows    ( mat_, 5UL );
      checkColumns ( mat_, 4UL );
      checkNonZeros( mat_, 7UL );

      if( sm(0,0) != 4 || sm(0,1) != 5 || sm(0,2) != -6 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 4  5 -6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major iterator-based erase function
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::erase( size_t, Iterator )";

      initialize();

      SMT sm = submatrix( mat_, 3UL, 1UL, 2UL, 3UL );

      // Erasing the non-zero element at the end of the 1st row
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.find( 1UL, 2UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 3UL );
         checkNonZeros( sm  , 5UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 9UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) !=  4 || sm(0,1) != 5 || sm(0,2) != -6 ||
             sm(1,0) != -8 || sm(1,1) != 9 || sm(1,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4  5 -6 )\n( -8  9  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the non-zero element at the beginning of the 1st row
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.find( 1UL, 0UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 3UL );
         checkNonZeros( sm  , 4UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 8UL );

         if( pos->value() != 9 || pos->index() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 9\n"
                << "   Expected index: 1\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 4 || sm(0,1) != 5 || sm(0,2) != -6 ||
             sm(1,0) != 0 || sm(1,1) != 9 || sm(1,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4  5 -6 )\n( 0  9  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the non-zero element at the beginning of the 1st row
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.find( 1UL, 1UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 3UL );
         checkNonZeros( sm  , 3UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 7UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 4 || sm(0,1) != 5 || sm(0,2) != -6 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4  5 -6 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an already erased element
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.find( 1UL, 2UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 3UL );
         checkNonZeros( sm  , 3UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 7UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 4 || sm(0,1) != 5 || sm(0,2) != -6 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 4  5 -6 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Row-major iterator-range-based erase function
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::erase( size_t, Iterator, Iterator )";

      initialize();

      SMT sm = submatrix( mat_, 3UL, 0UL, 2UL, 4UL );

      // Erasing the 0th row
      {
         SMT::Iterator pos = sm.erase( 0UL, sm.begin( 0UL ), sm.end( 0UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 4UL );
         checkNonZeros( sm  , 4UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 7UL );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) !=  0 || sm(0,2) != 0 || sm(0,3) !=  0 ||
             sm(1,0) != 7 || sm(1,1) != -8 || sm(1,2) != 9 || sm(1,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the 0th row failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0  0  0  0 )\n( 7 -8  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the first half of the 1st row
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.begin( 1UL ), sm.find( 1UL, 2UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 4UL );
         checkNonZeros( sm  , 2UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 5UL );

         if( pos->value() != 9 || pos->index() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 9\n"
                << "   Expected index: 2\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 0 || sm(0,3) !=  0 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 9 || sm(1,3) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the first half of the 1st row failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0  0  0  0 )\n( 0  0  9 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the second half of the 1st row
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.find( 1UL, 2UL ), sm.end( 1UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 4UL );
         checkNonZeros( sm  , 0UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 3UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 0 || sm(0,3) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 0 || sm(1,3) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the second half of the 1st row failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an empty range
      {
         SMT::Iterator pos = sm.erase( 1UL, sm.begin( 1UL ), sm.begin( 1UL ) );

         checkRows    ( sm  , 2UL );
         checkColumns ( sm  , 4UL );
         checkNonZeros( sm  , 0UL );
         checkRows    ( mat_, 5UL );
         checkColumns ( mat_, 4UL );
         checkNonZeros( mat_, 3UL );

         if( pos != sm.begin( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the given end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 0 || sm(0,3) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) != 0 || sm(1,3) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing an empty range failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 0 0 )\n( 0 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major index-based erase function
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::erase( size_t, size_t )";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 3UL, 3UL, 2UL );

      // Erasing the non-zero element at the end of the 1st column
      sm.erase( 2UL, 1UL );

      checkRows    ( sm   , 3UL );
      checkColumns ( sm   , 2UL );
      checkNonZeros( sm   , 5UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 9UL );

      if( sm(0,0) !=  4 || sm(0,1) != -8 ||
          sm(1,0) !=  5 || sm(1,1) !=  9 ||
          sm(2,0) != -6 || sm(2,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  4 -8 )\n(  5  9 )\n( -6  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the non-zero element at the beginning of the 1st column
      sm.erase( 0UL, 1UL );

      checkRows    ( sm   , 3UL );
      checkColumns ( sm   , 2UL );
      checkNonZeros( sm   , 4UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 8UL );

      if( sm(0,0) !=  4 || sm(0,1) != 0 ||
          sm(1,0) !=  5 || sm(1,1) != 9 ||
          sm(2,0) != -6 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  4 0 )\n(  5 9 )\n( -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the non-zero element at the beginning of the 1st column
      sm.erase( 1UL, 1UL );

      checkRows    ( sm   , 3UL );
      checkColumns ( sm   , 2UL );
      checkNonZeros( sm   , 3UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 7UL );

      if( sm(0,0) !=  4 || sm(0,1) != 0 ||
          sm(1,0) !=  5 || sm(1,1) != 0 ||
          sm(2,0) != -6 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  4 0 )\n(  5 0 )\n( -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase an already erased element
      sm.erase( 2UL, 1UL );

      checkRows    ( sm   , 3UL );
      checkColumns ( sm   , 2UL );
      checkNonZeros( sm   , 3UL );
      checkRows    ( tmat_, 4UL );
      checkColumns ( tmat_, 5UL );
      checkNonZeros( tmat_, 7UL );

      if( sm(0,0) !=  4 || sm(0,1) != 0 ||
          sm(1,0) !=  5 || sm(1,1) != 0 ||
          sm(2,0) != -6 || sm(2,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  4 0 )\n(  5 0 )\n( -6 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major iterator-based erase function
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::erase( size_t, Iterator )";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 3UL, 3UL, 2UL );

      // Erasing the non-zero element at the end of the 1st column
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.find( 2UL, 1UL ) );

         checkRows    ( sm   , 3UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 5UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 9UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) !=  4 || sm(0,1) != -8 ||
             sm(1,0) !=  5 || sm(1,1) !=  9 ||
             sm(2,0) != -6 || sm(2,1) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 -8 )\n(  5  9 )\n( -6  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the non-zero element at the beginning of the 1st column
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.find( 0UL, 1UL ) );

         checkRows    ( sm   , 3UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 4UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 8UL );

         if( pos->value() != 9 || pos->index() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 9\n"
                << "   Expected index: 1\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) !=  4 || sm(0,1) != 0 ||
             sm(1,0) !=  5 || sm(1,1) != 9 ||
             sm(2,0) != -6 || sm(2,1) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 0 )\n(  5 9 )\n( -6 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the non-zero element at the beginning of the 1st column
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.find( 1UL, 1UL ) );

         checkRows    ( sm   , 3UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 3UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 7UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) !=  4 || sm(0,1) != 0 ||
             sm(1,0) !=  5 || sm(1,1) != 0 ||
             sm(2,0) != -6 || sm(2,1) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 0 )\n(  5 0 )\n( -6 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an already erased element
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.find( 2UL, 1UL ) );

         checkRows    ( sm   , 3UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 3UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 7UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) !=  4 || sm(0,1) != 0 ||
             sm(1,0) !=  5 || sm(1,1) != 0 ||
             sm(2,0) != -6 || sm(2,1) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n(  4 0 )\n(  5 0 )\n( -6 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major iterator-range-based erase function
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::erase( size_t, Iterator, Iterator )";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 3UL, 4UL, 2UL );

      // Erasing the 0th column
      {
         OSMT::Iterator pos = sm.erase( 0UL, sm.begin( 0UL ), sm.end( 0UL ) );

         checkRows    ( sm   , 4UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 4UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 7UL );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) !=  7 ||
             sm(1,0) != 0 || sm(1,1) != -8 ||
             sm(2,0) != 0 || sm(2,1) !=  9 ||
             sm(3,0) != 0 || sm(3,1) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the 0th column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0  7 )\n( 0 -8 )\n( 0  9 )\n( 0 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the first half of the 1st column
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.begin( 1UL ), sm.find( 2UL, 1UL ) );

         checkRows    ( sm   , 4UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 2UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 5UL );

         if( pos->value() != 9 || pos->index() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 9\n"
                << "   Expected index: 2\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) !=  0 ||
             sm(1,0) != 0 || sm(1,1) !=  0 ||
             sm(2,0) != 0 || sm(2,1) !=  9 ||
             sm(3,0) != 0 || sm(3,1) != 10 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the 0th column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0  0 )\n( 0  0 )\n( 0  9 )\n( 0 10 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the second half of the 1st column
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.find( 2UL, 1UL ), sm.end( 1UL ) );

         checkRows    ( sm   , 4UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 0UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 3UL );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 ||
             sm(2,0) != 0 || sm(2,1) != 0 ||
             sm(3,0) != 0 || sm(3,1) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the 0th column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 )\n( 0 0 )\n( 0 0 )\n( 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an empty range
      {
         OSMT::Iterator pos = sm.erase( 1UL, sm.begin( 1UL ), sm.begin( 1UL ) );

         checkRows    ( sm   , 4UL );
         checkColumns ( sm   , 2UL );
         checkNonZeros( sm   , 0UL );
         checkRows    ( tmat_, 4UL );
         checkColumns ( tmat_, 5UL );
         checkNonZeros( tmat_, 3UL );

         if( pos != sm.begin( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the given end() iterator\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm(0,0) != 0 || sm(0,1) != 0 ||
             sm(1,0) != 0 || sm(1,1) != 0 ||
             sm(2,0) != 0 || sm(2,1) != 0 ||
             sm(3,0) != 0 || sm(3,1) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing the 0th column failed\n"
                << " Details:\n"
                << "   Result:\n" << sm << "\n"
                << "   Expected result:\n( 0 0 )\n( 0 0 )\n( 0 0 )\n( 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reserve() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reserve() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testReserve()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::reserve()";

      MT mat( 3UL, 20UL );

      SMT sm = submatrix( mat, 1UL, 0UL, 1UL, 20UL );

      // Increasing the capacity of the matrix
      sm.reserve( 10UL );

      checkRows    ( sm,  1UL );
      checkColumns ( sm, 20UL );
      checkCapacity( sm, 10UL );
      checkNonZeros( sm,  0UL );

      // Further increasing the capacity of the matrix
      sm.reserve( 20UL );

      checkRows    ( sm,  1UL );
      checkColumns ( sm, 20UL );
      checkCapacity( sm, 20UL );
      checkNonZeros( sm,  0UL );
   }

   {
      test_ = "Row-major SparseSubmatrix::reserve( size_t )";

      MT mat( 3UL, 20UL );

      SMT sm = submatrix( mat, 1UL, 0UL, 1UL, 20UL );

      // Increasing the capacity of the row
      sm.reserve( 0UL, 10UL );

      checkRows    ( sm,  1UL );
      checkColumns ( sm, 20UL );
      checkCapacity( sm, 10UL );
      checkNonZeros( sm,  0UL );

      // Further increasing the capacity of the row
      sm.reserve( 0UL, 15UL );

      checkRows    ( sm,  1UL );
      checkColumns ( sm, 20UL );
      checkCapacity( sm, 15UL );
      checkNonZeros( sm,  0UL );
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::reserve()";

      OMT mat( 3UL, 20UL );

      OSMT sm = submatrix( mat, 1UL, 0UL, 1UL, 20UL );

      // Increasing the capacity of the matrix
      sm.reserve( 10UL );

      checkRows    ( sm,  1UL );
      checkColumns ( sm, 20UL );
      checkCapacity( sm, 10UL );
      checkNonZeros( sm,  0UL );

      // Further increasing the capacity of the matrix
      sm.reserve( 20UL );

      checkRows    ( sm,  1UL );
      checkColumns ( sm, 20UL );
      checkCapacity( sm, 20UL );
      checkNonZeros( sm,  0UL );
   }

   {
      test_ = "Columnt-major SparseSubmatrix::reserve( size_t )";

      OMT mat( 20UL, 3UL );

      OSMT sm = submatrix( mat, 0UL, 1UL, 20UL, 1UL );

      // Increasing the capacity of the column
      sm.reserve( 0UL, 10UL );

      checkRows    ( sm, 20UL );
      checkColumns ( sm,  1UL );
      checkCapacity( sm, 10UL );
      checkNonZeros( sm,  0UL );

      // Further increasing the capacity of the column
      sm.reserve( 0UL, 15UL );

      checkRows    ( sm, 20UL );
      checkColumns ( sm,  1UL );
      checkCapacity( sm, 15UL );
      checkNonZeros( sm,  0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c trim() member functions of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c trim() member functions of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testTrim()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major CompressedMatrix::trim()";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      // Increasing the row capacity of the matrix
      sm.reserve( 0UL, 10UL );
      sm.reserve( 1UL, 20UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkCapacity( sm  , 30UL );
      checkCapacity( sm  ,  0UL, 10UL );
      checkCapacity( sm  ,  1UL, 20UL );
      checkCapacity( mat_, 30UL );
      checkCapacity( mat_,  2UL, 10UL );
      checkCapacity( mat_,  3UL, 20UL );

      // Trimming the matrix
      sm.trim();

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkCapacity( sm  , 30UL );
      checkCapacity( sm  ,  0UL, sm.nonZeros( 0UL ) );
      checkCapacity( sm  ,  1UL, sm.nonZeros( 1UL ) );
      checkCapacity( mat_, 30UL );
      checkCapacity( mat_,  2UL, mat_.nonZeros( 2UL ) );
      checkCapacity( mat_,  3UL, mat_.nonZeros( 3UL ) );
   }

   {
      test_ = "Row-major CompressedMatrix::trim( size_t )";

      initialize();

      SMT sm = submatrix( mat_, 2UL, 1UL, 2UL, 3UL );

      // Increasing the row capacity of the matrix
      sm.reserve( 0UL, 10UL );
      sm.reserve( 1UL, 20UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkCapacity( sm  , 30UL );
      checkCapacity( sm  ,  0UL, 10UL );
      checkCapacity( sm  ,  1UL, 20UL );
      checkCapacity( mat_, 30UL );
      checkCapacity( mat_,  2UL, 10UL );
      checkCapacity( mat_,  3UL, 20UL );

      // Trimming the 0th row
      sm.trim( 0UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkCapacity( sm  , 30UL );
      checkCapacity( sm  ,  0UL, sm.nonZeros( 0UL ) );
      checkCapacity( sm  ,  1UL, 30UL - sm.nonZeros( 0UL ) );
      checkCapacity( mat_, 30UL );
      checkCapacity( mat_,  2UL, mat_.nonZeros( 2UL ) );
      checkCapacity( mat_,  3UL, 30UL - mat_.nonZeros( 2UL ) );

      // Trimming the 1st row
      sm.trim( 1UL );

      checkRows    ( sm  ,  2UL );
      checkColumns ( sm  ,  3UL );
      checkCapacity( sm  , 30UL );
      checkCapacity( sm  ,  0UL, sm.nonZeros( 0UL ) );
      checkCapacity( sm  ,  1UL, sm.nonZeros( 1UL ) );
      checkCapacity( mat_, 30UL );
      checkCapacity( mat_,  2UL, mat_.nonZeros( 2UL ) );
      checkCapacity( mat_,  3UL, mat_.nonZeros( 3UL ) );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major CompressedMatrix::trim()";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      // Increasing the row capacity of the matrix
      sm.reserve( 0UL, 10UL );
      sm.reserve( 1UL, 20UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkCapacity( sm   , 30UL );
      checkCapacity( sm   ,  0UL, 10UL );
      checkCapacity( sm   ,  1UL, 20UL );
      checkCapacity( tmat_, 30UL );
      checkCapacity( tmat_,  2UL, 10UL );
      checkCapacity( tmat_,  3UL, 20UL );

      // Trimming the matrix
      sm.trim();

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkCapacity( sm   , 30UL );
      checkCapacity( sm   ,  0UL, sm.nonZeros( 0UL ) );
      checkCapacity( sm   ,  1UL, sm.nonZeros( 1UL ) );
      checkCapacity( tmat_, 30UL );
      checkCapacity( tmat_,  2UL, tmat_.nonZeros( 2UL ) );
      checkCapacity( tmat_,  3UL, tmat_.nonZeros( 3UL ) );
   }

   {
      test_ = "Column-major CompressedMatrix::trim( size_t )";

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 2UL, 3UL, 2UL );

      // Increasing the row capacity of the matrix
      sm.reserve( 0UL, 10UL );
      sm.reserve( 1UL, 20UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkCapacity( sm   , 30UL );
      checkCapacity( sm   ,  0UL, 10UL );
      checkCapacity( sm   ,  1UL, 20UL );
      checkCapacity( tmat_, 30UL );
      checkCapacity( tmat_,  2UL, 10UL );
      checkCapacity( tmat_,  3UL, 20UL );

      // Trimming the 0th row
      sm.trim( 0UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkCapacity( sm   , 30UL );
      checkCapacity( sm   ,  0UL, sm.nonZeros( 0UL ) );
      checkCapacity( sm   ,  1UL, 30UL - sm.nonZeros( 0UL ) );
      checkCapacity( tmat_, 30UL );
      checkCapacity( tmat_,  2UL, tmat_.nonZeros( 2UL ) );
      checkCapacity( tmat_,  3UL, 30UL - tmat_.nonZeros( 2UL ) );

      // Trimming the 1st row
      sm.trim( 1UL );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  2UL );
      checkCapacity( sm   , 30UL );
      checkCapacity( sm   ,  0UL, sm.nonZeros( 0UL ) );
      checkCapacity( sm   ,  1UL, sm.nonZeros( 1UL ) );
      checkCapacity( tmat_, 30UL );
      checkCapacity( tmat_,  2UL, tmat_.nonZeros( 2UL ) );
      checkCapacity( tmat_,  3UL, tmat_.nonZeros( 3UL ) );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c transpose() member functions of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c transpose() member function of the SparseSubmatrix
// class template. Additionally, it performs a test of self-transpose via the \c trans()
// function. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testTranspose()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major self-transpose via DenseSubmatrix::transpose()";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 3UL );

      sm.transpose();

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  5UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) != 0 ||
          sm(1,0) != 1 || sm(1,1) !=  0 || sm(1,2) != 4 ||
          sm(2,0) != 0 || sm(2,1) != -3 || sm(2,2) != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -2 0 )\n( 1  0 4 )\n( 0 -3 5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) != -2 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 1 || mat_(2,1) !=  0 || mat_(2,2) != 4 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) != -3 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 -2  0  0 )\n"
                                     "(  1  0  4  0 )\n"
                                     "(  0 -3  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major self-transpose via trans()";

      initialize();

      SMT sm = submatrix( mat_, 1UL, 0UL, 3UL, 3UL );

      sm = trans( sm );

      checkRows    ( sm  ,  3UL );
      checkColumns ( sm  ,  3UL );
      checkNonZeros( sm  ,  5UL );
      checkRows    ( mat_,  5UL );
      checkColumns ( mat_,  4UL );
      checkNonZeros( mat_, 10UL );

      if( sm(0,0) != 0 || sm(0,1) != -2 || sm(0,2) != 0 ||
          sm(1,0) != 1 || sm(1,1) !=  0 || sm(1,2) != 4 ||
          sm(2,0) != 0 || sm(2,1) != -3 || sm(2,2) != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -2 0 )\n( 1  0 4 )\n( 0 -3 5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( mat_(0,0) != 0 || mat_(0,1) !=  0 || mat_(0,2) != 0 || mat_(0,3) !=  0 ||
          mat_(1,0) != 0 || mat_(1,1) != -2 || mat_(1,2) != 0 || mat_(1,3) !=  0 ||
          mat_(2,0) != 1 || mat_(2,1) !=  0 || mat_(2,2) != 4 || mat_(2,3) !=  0 ||
          mat_(3,0) != 0 || mat_(3,1) != -3 || mat_(3,2) != 5 || mat_(3,3) != -6 ||
          mat_(4,0) != 7 || mat_(4,1) != -8 || mat_(4,2) != 9 || mat_(4,3) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << mat_ << "\n"
             << "   Expected result:\n(  0  0  0  0 )\n"
                                     "(  0 -2  0  0 )\n"
                                     "(  1  0  4  0 )\n"
                                     "(  0 -3  5 -6 )\n"
                                     "(  7 -8  9 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major self-transpose via DenseSubmatrix::transpose()";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 3UL );

      sm.transpose();

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  3UL );
      checkNonZeros( sm   ,  5UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) !=  0 || sm(0,1) != 1 || sm(0,2) !=  0 ||
          sm(1,0) != -2 || sm(1,1) != 0 || sm(1,2) != -3 ||
          sm(2,0) !=  0 || sm(2,1) != 4 || sm(2,2) !=  5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  1  0 )\n( -2  0 -3 )\n(  0  4  5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 1 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != -2 || tmat_(1,2) != 0 || tmat_(1,3) != -3 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 4 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) != 0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  1  0  7 )\n"
                                     "(  0 -2  0 -3 -8 )\n"
                                     "(  0  0  4  5  9 )\n"
                                     "(  0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major self-transpose via trans()";

      initialize();

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 3UL, 3UL );

      sm = trans( sm );

      checkRows    ( sm   ,  3UL );
      checkColumns ( sm   ,  3UL );
      checkNonZeros( sm   ,  5UL );
      checkRows    ( tmat_,  4UL );
      checkColumns ( tmat_,  5UL );
      checkNonZeros( tmat_, 10UL );

      if( sm(0,0) !=  0 || sm(0,1) != 1 || sm(0,2) !=  0 ||
          sm(1,0) != -2 || sm(1,1) != 0 || sm(1,2) != -3 ||
          sm(2,0) !=  0 || sm(2,1) != 4 || sm(2,2) !=  5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n(  0  1  0 )\n( -2  0 -3 )\n(  0  4  5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( tmat_(0,0) != 0 || tmat_(0,1) !=  0 || tmat_(0,2) != 1 || tmat_(0,3) !=  0 || tmat_(0,4) !=  7 ||
          tmat_(1,0) != 0 || tmat_(1,1) != -2 || tmat_(1,2) != 0 || tmat_(1,3) != -3 || tmat_(1,4) != -8 ||
          tmat_(2,0) != 0 || tmat_(2,1) !=  0 || tmat_(2,2) != 4 || tmat_(2,3) !=  5 || tmat_(2,4) !=  9 ||
          tmat_(3,0) != 0 || tmat_(3,1) !=  0 || tmat_(3,2) != 0 || tmat_(3,3) != -6 || tmat_(3,4) != 10 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Transpose operation failed\n"
             << " Details:\n"
             << "   Result:\n" << tmat_ << "\n"
             << "   Expected result:\n(  0  0  1  0  7 )\n"
                                     "(  0 -2  0 -3 -8 )\n"
                                     "(  0  0  4  5  9 )\n"
                                     "(  0  0  0 -6 10 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c find() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c find() member function of the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testFind()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::find()";

      typedef SMT::ConstIterator  ConstIterator;

      initialize();

      SMT sm = submatrix( mat_, 1UL, 1UL, 3UL, 2UL );

      checkRows    ( sm, 3UL );
      checkColumns ( sm, 2UL );
      checkNonZeros( sm, 4UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 1UL );
      checkNonZeros( sm, 2UL, 2UL );

      // Searching for the first element
      {
         ConstIterator pos( sm.find( 0UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (0,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 0 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 0\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for the second element
      {
         ConstIterator pos( sm.find( 1UL, 1UL ) );

         if( pos == sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (1,1)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != -3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = -3\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for a non-existing non-zero element
      {
         ConstIterator pos( sm.find( 1UL, 0UL ) );

         if( pos != sm.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Non-existing element could be found\n"
                << " Details:\n"
                << "   Required index = 0\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 0\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::find()";

      typedef OSMT::ConstIterator  ConstIterator;

      initialize();

      OSMT sm = submatrix( tmat_, 1UL, 1UL, 2UL, 3UL );

      checkRows    ( sm, 2UL );
      checkColumns ( sm, 3UL );
      checkNonZeros( sm, 4UL );
      checkNonZeros( sm, 0UL, 1UL );
      checkNonZeros( sm, 1UL, 1UL );
      checkNonZeros( sm, 2UL, 2UL );

      // Searching for the first element
      {
         ConstIterator pos( sm.find( 0UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (0,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 0 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 0\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for the second element
      {
         ConstIterator pos( sm.find( 1UL, 2UL ) );

         if( pos == sm.end( 2UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (1,2)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 5\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for a non-existing non-zero element
      {
         ConstIterator pos( sm.find( 1UL, 0UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Non-existing element could be found\n"
                << " Details:\n"
                << "   Required index = 0\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 0\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c lowerBound() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c lowerBound() member function of the SparseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testLowerBound()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::lowerBound()";

      typedef SMT::ConstIterator  ConstIterator;

      SMT sm = submatrix( mat_, 1UL, 0UL, 1UL, 4UL );

      checkRows    ( sm, 1UL );
      checkColumns ( sm, 4UL );
      checkNonZeros( sm, 1UL );
      checkNonZeros( sm, 0UL, 1UL );

      // Determining the lower bound for position (0,0)
      {
         ConstIterator pos( sm.lowerBound( 0UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (0,1)
      {
         ConstIterator pos( sm.lowerBound( 0UL, 1UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,1)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (0,2)
      {
         ConstIterator pos( sm.lowerBound( 0UL, 2UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,2)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::lowerBound()";

      typedef OSMT::ConstIterator  ConstIterator;

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 4UL, 1UL );

      checkRows    ( sm, 4UL );
      checkColumns ( sm, 1UL );
      checkNonZeros( sm, 1UL );
      checkNonZeros( sm, 0UL, 1UL );

      // Determining the lower bound for position (0,0)
      {
         ConstIterator pos( sm.lowerBound( 0UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (1,0)
      {
         ConstIterator pos( sm.lowerBound( 1UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (2,0)
      {
         ConstIterator pos( sm.lowerBound( 2UL, 0UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (2,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c upperBound() member function of the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c upperBound() member function of the SparseSubmatrix
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testUpperBound()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major SparseSubmatrix::upperBound()";

      typedef SMT::ConstIterator  ConstIterator;

      SMT sm = submatrix( mat_, 1UL, 0UL, 1UL, 4UL );

      checkRows    ( sm, 1UL );
      checkColumns ( sm, 4UL );
      checkNonZeros( sm, 1UL );
      checkNonZeros( sm, 0UL, 1UL );

      // Determining the upper bound for position (0,0)
      {
         ConstIterator pos( sm.upperBound( 0UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (0,1)
      {
         ConstIterator pos( sm.upperBound( 0UL, 1UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,1)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (0,2)
      {
         ConstIterator pos( sm.upperBound( 0UL, 2UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,2)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major SparseSubmatrix::upperBound()";

      typedef OSMT::ConstIterator  ConstIterator;

      OSMT sm = submatrix( tmat_, 0UL, 1UL, 4UL, 1UL );

      checkRows    ( sm, 4UL );
      checkColumns ( sm, 1UL );
      checkNonZeros( sm, 1UL );
      checkNonZeros( sm, 0UL, 1UL );

      // Determining the upper bound for position (0,0)
      {
         ConstIterator pos( sm.upperBound( 0UL, 0UL ) );

         if( pos == sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (0,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (1,0)
      {
         ConstIterator pos( sm.upperBound( 1UL, 0UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (2,0)
      {
         ConstIterator pos( sm.upperBound( 2UL, 0UL ) );

         if( pos != sm.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (2,0)\n"
                << "   Current submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isDefault() function with the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isDefault() function with the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIsDefault()
{
   using blaze::isDefault;


   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major isDefault() function";

      initialize();

      // isDefault with default submatrix
      {
         SMT sm = submatrix( mat_, 0UL, 0UL, 1UL, 4UL );

         if( isDefault( sm(0,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix element: " << sm(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( sm ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default submatrix
      {
         SMT sm = submatrix( mat_, 1UL, 0UL, 1UL, 4UL );

         if( isDefault( sm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major isDefault() function";

      initialize();

      // isDefault with default submatrix
      {
         OSMT sm = submatrix( tmat_, 0UL, 0UL, 4UL, 1UL );

         if( isDefault( sm(1,0) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix element: " << sm(1,0) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( sm ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default submatrix
      {
         OSMT sm = submatrix( tmat_, 0UL, 1UL, 4UL, 1UL );

         if( isDefault( sm ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isSame() function with the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isSame() function with the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIsSame()
{
   //=====================================================================================
   // Row-major submatrix tests
   //=====================================================================================

   {
      test_ = "Row-major isSame() function";

      // isSame with matrix and matching submatrix
      {
         SMT sm = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );

         if( blaze::isSame( sm, mat_ ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat_, sm ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of rows)
      {
         SMT sm = submatrix( mat_, 0UL, 0UL, 4UL, 4UL );

         if( blaze::isSame( sm, mat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of columns)
      {
         SMT sm = submatrix( mat_, 0UL, 0UL, 5UL, 3UL );

         if( blaze::isSame( sm, mat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different row index)
      {
         SMT sm = submatrix( mat_, 1UL, 0UL, 4UL, 4UL );

         if( blaze::isSame( sm, mat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different column index)
      {
         SMT sm = submatrix( mat_, 0UL, 1UL, 5UL, 3UL );

         if( blaze::isSame( sm, mat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( mat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << mat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching submatrices
      {
         SMT sm1 = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );
         SMT sm2 = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );

         if( blaze::isSame( sm1, sm2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of rows)
      {
         SMT sm1 = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );
         SMT sm2 = submatrix( mat_, 0UL, 0UL, 4UL, 4UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of columns)
      {
         SMT sm1 = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );
         SMT sm2 = submatrix( mat_, 0UL, 0UL, 5UL, 3UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different row index)
      {
         SMT sm1 = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );
         SMT sm2 = submatrix( mat_, 1UL, 0UL, 4UL, 4UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different column index)
      {
         SMT sm1 = submatrix( mat_, 0UL, 0UL, 5UL, 4UL );
         SMT sm2 = submatrix( mat_, 0UL, 1UL, 5UL, 3UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major submatrix tests
   //=====================================================================================

   {
      test_ = "Column-major isSame() function";

      // isSame with matrix and matching submatrix
      {
         OSMT sm = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );

         if( blaze::isSame( sm, tmat_ ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat_, sm ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of rows)
      {
         OSMT sm = submatrix( tmat_, 0UL, 0UL, 3UL, 5UL );

         if( blaze::isSame( sm, tmat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different number of columns)
      {
         OSMT sm = submatrix( tmat_, 0UL, 0UL, 4UL, 4UL );

         if( blaze::isSame( sm, tmat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different row index)
      {
         OSMT sm = submatrix( tmat_, 1UL, 0UL, 3UL, 5UL );

         if( blaze::isSame( sm, tmat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matrix and non-matching submatrix (different column index)
      {
         OSMT sm = submatrix( tmat_, 0UL, 1UL, 4UL, 4UL );

         if( blaze::isSame( sm, tmat_ ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( blaze::isSame( tmat_, sm ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << tmat_ << "\n"
                << "   Submatrix:\n" << sm << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with matching submatrices
      {
         OSMT sm1 = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );
         OSMT sm2 = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );

         if( blaze::isSame( sm1, sm2 ) == false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of rows)
      {
         OSMT sm1 = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );
         OSMT sm2 = submatrix( tmat_, 0UL, 0UL, 3UL, 5UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different number of columns)
      {
         OSMT sm1 = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );
         OSMT sm2 = submatrix( tmat_, 0UL, 0UL, 4UL, 4UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different row index)
      {
         OSMT sm1 = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );
         OSMT sm2 = submatrix( tmat_, 1UL, 0UL, 3UL, 5UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isSame with non-matching submatrices (different column index)
      {
         OSMT sm1 = submatrix( tmat_, 0UL, 0UL, 4UL, 5UL );
         OSMT sm2 = submatrix( tmat_, 0UL, 1UL, 4UL, 4UL );

         if( blaze::isSame( sm1, sm2 ) == true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isSame evaluation\n"
                << " Details:\n"
                << "   First submatrix:\n" << sm1 << "\n"
                << "   Second submatrix:\n" << sm2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c submatrix() function with the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c submatrix() function with the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testSubmatrix()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major submatrix() function";

      initialize();

      {
         SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
         SMT sm2 = submatrix( sm1 , 1UL, 1UL, 3UL, 2UL );

         if( sm2(1,1) != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator access failed\n"
                << " Details:\n"
                << "   Result: " << sm2(1,1) << "\n"
                << "   Expected result: -6\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm2.begin(1UL)->value() != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator access failed\n"
                << " Details:\n"
                << "   Result: " << sm2.begin(1UL)->value() << "\n"
                << "   Expected result: 5\n";
            throw std::runtime_error( oss.str() );
         }
      }

      try {
         SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
         SMT sm2 = submatrix( sm1 , 4UL, 1UL, 3UL, 2UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
         SMT sm2 = submatrix( sm1 , 1UL, 3UL, 3UL, 2UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
         SMT sm2 = submatrix( sm1 , 1UL, 1UL, 4UL, 2UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
         SMT sm2 = submatrix( sm1 , 1UL, 1UL, 3UL, 3UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major submatrix() function";

      initialize();

      {
         OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
         OSMT sm2 = submatrix( sm1  , 1UL, 1UL, 2UL, 3UL );

         if( sm2(1,1) != -6 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Function call operator access failed\n"
                << " Details:\n"
                << "   Result: " << sm2(1,1) << "\n"
                << "   Expected result: -6\n";
            throw std::runtime_error( oss.str() );
         }

         if( sm2.begin(1UL)->value() != 5 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator access failed\n"
                << " Details:\n"
                << "   Result: " << sm2.begin(1UL)->value() << "\n"
                << "   Expected result: 5\n";
            throw std::runtime_error( oss.str() );
         }
      }

      try {
         OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
         OSMT sm2 = submatrix( sm1  , 3UL, 1UL, 2UL, 3UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
         OSMT sm2 = submatrix( sm1  , 1UL, 4UL, 2UL, 3UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
         OSMT sm2 = submatrix( sm1  , 1UL, 1UL, 3UL, 3UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      try {
         OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
         OSMT sm2 = submatrix( sm1  , 1UL, 1UL, 2UL, 4UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of out-of-bounds submatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << sm2 << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c row() function with the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c row() function with the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testRow()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major row() function";

      initialize();

      typedef blaze::SparseRow<SMT>  RowType;

      SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
      RowType row1 = row( sm1, 1UL );

      if( row1[1] != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }

      if( row1.begin()->value() != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << row1.begin()->value() << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major row() function";

      initialize();

      typedef blaze::SparseRow<OSMT>  RowType;

      OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
      RowType row1 = row( sm1, 1UL );

      if( row1[1] != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }

      if( row1.begin()->value() != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << row1.begin()->value() << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c column() function with the SparseSubmatrix class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c column() function with the SparseSubmatrix class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testColumn()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major column() function";

      initialize();

      typedef blaze::SparseColumn<SMT>  ColumnType;

      SMT sm1 = submatrix( mat_, 1UL, 1UL, 4UL, 3UL );
      ColumnType col1 = column( sm1, 1UL );

      if( col1[1] != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }

      if( col1.begin()->value() != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << col1.begin()->value() << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major column() function";

      initialize();

      typedef blaze::SparseColumn<OSMT>  ColumnType;

      OSMT sm1 = submatrix( tmat_, 1UL, 1UL, 3UL, 4UL );
      ColumnType col1 = column( sm1, 1UL );

      if( col1[1] != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subscript operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }

      if( col1.begin()->value() != -3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << col1.begin()->value() << "\n"
             << "   Expected result: -3\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Initialization of all member matrices.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function initializes all member matrices to specific predetermined values.
*/
void ClassTest::initialize()
{
   // Initializing the row-major compressed matrix
   mat_.reset();
   mat_(1,1) =  1;
   mat_(2,0) = -2;
   mat_(2,2) = -3;
   mat_(3,1) =  4;
   mat_(3,2) =  5;
   mat_(3,3) = -6;
   mat_(4,0) =  7;
   mat_(4,1) = -8;
   mat_(4,2) =  9;
   mat_(4,3) = 10;

   // Initializing the column-major compressed matrix
   tmat_.reset();
   tmat_(1,1) =  1;
   tmat_(0,2) = -2;
   tmat_(2,2) = -3;
   tmat_(1,3) =  4;
   tmat_(2,3) =  5;
   tmat_(3,3) = -6;
   tmat_(0,4) =  7;
   tmat_(1,4) = -8;
   tmat_(2,4) =  9;
   tmat_(3,4) = 10;
}
//*************************************************************************************************

} // namespace sparsesubmatrix

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running SparseSubmatrix class test..." << std::endl;

   try
   {
      RUN_SPARSESUBMATRIX_CLASS_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during SparseSubmatrix class test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
