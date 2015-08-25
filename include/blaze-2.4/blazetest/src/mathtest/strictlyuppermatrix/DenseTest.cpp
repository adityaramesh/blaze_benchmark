//=================================================================================================
/*!
//  \file src/mathtest/strictlyuppermatrix/DenseTest.cpp
//  \brief Source file for the StrictlyUpperMatrix dense test
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
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/CompressedVector.h>
#include <blaze/math/DenseColumn.h>
#include <blaze/math/DenseRow.h>
#include <blaze/math/DenseSubmatrix.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/HybridMatrix.h>
#include <blaze/math/StaticMatrix.h>
#include <blaze/util/Complex.h>
#include <blazetest/mathtest/strictlyuppermatrix/DenseTest.h>


namespace blazetest {

namespace mathtest {

namespace strictlyuppermatrix {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the StrictlyUpperMatrix dense test.
//
// \exception std::runtime_error Operation error detected.
*/
DenseTest::DenseTest()
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
   testResize();
   testExtend();
   testReserve();
   testSwap();
   testIsDefault();
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
/*!\brief Test of the StrictlyUpperMatrix constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the StrictlyUpperMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testConstructors()
{
   //=====================================================================================
   // Row-major default constructor
   //=====================================================================================

   // Default constructor (StaticMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix default constructor (StaticMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );
   }

   // Default constructor (HybridMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix default constructor (HybridMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::rowMajor> > upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Default constructor (DynamicMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix default constructor (DynamicMatrix)";

      const UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Row-major single argument constructor
   //=====================================================================================

   // Single argument constructor (StaticMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (StaticMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,2UL,2UL,blaze::rowMajor> > upper( 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 5 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (HybridMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (HybridMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::rowMajor> > upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (DynamicMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (DynamicMatrix)";

      const UT upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (0x0)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (0x0)";

      const blaze::DynamicMatrix<int,blaze::rowMajor> mat;
      const UT upper( mat );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Single argument constructor (strictly upper)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (strictly upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;

      const UT upper( mat );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (non-upper)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         const UT upper( mat );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of non-upper StrictlyUpperMatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Single argument constructor (StrictlyUpperMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix single argument constructor (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const UT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major two argument constructor
   //=====================================================================================

   // Two argument constructor (HybridMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix two argument constructor (HybridMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::rowMajor> > upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 5 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Two argument constructor (DynamicMatrix)
   {
      test_ = "Row-major StrictlyUpperMatrix two argument constructor (DynamicMatrix)";

      const UT upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 5 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major copy constructor
   //=====================================================================================

   // Copy constructor (0x0)
   {
      test_ = "Row-major StrictlyUpperMatrix copy constructor (0x0)";

      const UT upper1;
      const UT upper2( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy constructor (3x3)
   {
      test_ = "Row-major StrictlyUpperMatrix copy constructor (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const UT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major default constructor
   //=====================================================================================

   // Default constructor (StaticMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix default constructor (StaticMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );
   }

   // Default constructor (HybridMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix default constructor (HybridMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::columnMajor> > upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Default constructor (DynamicMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix default constructor (DynamicMatrix)";

      const OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major single argument constructor
   //=====================================================================================

   // Single argument constructor (StaticMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (StaticMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,2UL,2UL,blaze::columnMajor> > upper( 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 5 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (HybridMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (HybridMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::columnMajor> > upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (DynamicMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (DynamicMatrix)";

      const OUT upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (0x0)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (0x0)";

      const blaze::DynamicMatrix<int,blaze::columnMajor> mat;
      const OUT upper( mat );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Single argument constructor (strictly upper)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (strictly upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;

      const OUT upper( mat );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Single argument constructor (non-upper)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         const OUT upper( mat );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of non-upper StrictlyUpperMatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Single argument constructor (StrictlyUpperMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix single argument constructor (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const OUT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major two argument constructor
   //=====================================================================================

   // Two argument constructor (HybridMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix two argument constructor (HybridMatrix)";

      const blaze::StrictlyUpperMatrix< blaze::HybridMatrix<int,3UL,3UL,blaze::columnMajor> > upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 5 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Two argument constructor (DynamicMatrix)
   {
      test_ = "Column-major StrictlyUpperMatrix two argument constructor (DynamicMatrix)";

      const OUT upper( 2UL, 5 );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 5 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 5 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy constructor
   //=====================================================================================

   // Copy constructor (0x0)
   {
      test_ = "Column-major StrictlyUpperMatrix copy constructor (0x0)";

      const OUT upper1;
      const OUT upper2( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy constructor (3x3)
   {
      test_ = "Column-major StrictlyUpperMatrix copy constructor (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const OUT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StrictlyUpperMatrix assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testAssignment()
{
   //=====================================================================================
   // Row-major homogeneous assignment
   //=====================================================================================

   // Homogeneous assignment (3x3)
   {
      test_ = "Row-major StrictlyUpperMatrix homogeneous assignment (3x3)";

      UT upper( 3UL );
      upper = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 2 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major copy assignment
   //=====================================================================================

   // Copy assignment (0x0)
   {
      test_ = "Row-major StrictlyUpperMatrix copy assignment (0x0)";

      UT upper1, upper2;

      upper2 = upper1;

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy assignment (3x3)
   {
      test_ = "Row-major StrictlyUpperMatrix copy assignment (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Row-major StrictlyUpperMatrix dense matrix assignment (0x0)";

      const blaze::DynamicMatrix<int,blaze::rowMajor> mat;

      UT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Row-major/row-major dense matrix assignment (strictly upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix assignment (strictly upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix assignment (strictly upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix assignment (strictly upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix assignment (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix assignment (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Row-major StrictlyUpperMatrix sparse matrix assignment (0x0)";

      const blaze::CompressedMatrix<int,blaze::rowMajor> mat;

      UT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Row-major/row-major sparse matrix assignment (strictly upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat.insert( 1UL, 0UL, 0 );

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix assignment (strictly upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat.insert( 1UL, 0UL, 0 );

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 2UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 2UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 0UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major homogeneous assignment
   //=====================================================================================

   // Homogeneous assignment (3x3)
   {
      test_ = "Column-major StrictlyUpperMatrix homogeneous assignment (3x3)";

      OUT upper( 3UL );
      upper = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 2 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy assignment
   //=====================================================================================

   // Copy assignment (0x0)
   {
      test_ = "Column-major StrictlyUpperMatrix copy assignment (0x0)";

      OUT upper1, upper2;

      upper2 = upper1;

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy assignment (3x3)
   {
      test_ = "Column-major StrictlyUpperMatrix copy assignment (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Column-major StrictlyUpperMatrix dense matrix assignment (0x0)";

      const blaze::DynamicMatrix<int,blaze::columnMajor> mat;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Column-major/row-major dense matrix assignment (strictly upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix assignment (strictly upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix assignment (strictly upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix assignment (strictly upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix assignment (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix assignment (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Column-major StrictlyUpperMatrix sparse matrix assignment (0x0)";

      const blaze::CompressedMatrix<int,blaze::rowMajor> mat;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Column-major/row-major sparse matrix assignment (strictly upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix assignment (strictly upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 3UL );
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(2,0) =  5;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 2UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 2UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StrictlyUpperMatrix addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testAddAssign()
{
   //=====================================================================================
   // Row-major dense matrix addition assignment
   //=====================================================================================

   // Row-major/row-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix addition assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix addition assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix addition assignment (StrictlyUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix addition assignment (StrictlyUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix addition assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix addition assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix addition assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix addition assignment
   //=====================================================================================

   // Column-major/row-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix addition assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix addition assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix addition assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix addition assignment (StrictlyUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix addition assignment (StrictlyUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix addition assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix addition assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix addition assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix addition assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix addition assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix addition assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 3UL );
      upper1(0,1) =  2;
      upper1(0,2) = -7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 += upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) != 0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != 5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StrictlyUpperMatrix subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testSubAssign()
{
   //=====================================================================================
   // Row-major dense matrix subtraction assignment
   //=====================================================================================

   // Row-major/row-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix subtraction assignment (StrictlyUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix subtraction assignment (StrictlyUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix subtraction assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix subtraction assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix subtraction assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix subtraction assignment
   //=====================================================================================

   // Column-major/row-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix subtraction assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix subtraction assignment (StrictlyUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix subtraction assignment (StrictlyUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix subtraction assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix subtraction assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix subtraction assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix subtraction assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix subtraction assignment (StrictlyUpperMatrix)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix subtraction assignment (StrictlyUpperMatrix)";

      blaze::StrictlyUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 3UL );
      upper1(0,1) = -2;
      upper1(0,2) =  7;
      upper1(1,2) =  5;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 -= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 9UL );
      checkNonZeros( upper2, 2UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != -2 || upper2(0,2) !=  0 ||
          upper2(1,0) != 0 || upper2(1,1) !=  0 || upper2(1,2) != -5 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 -2  0 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StrictlyUpperMatrix multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the
// StrictlyUpperMatrix specialization. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void DenseTest::testMultAssign()
{
   //=====================================================================================
   // Row-major dense matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major dense matrix multiplication assignment (upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix multiplication assignment (upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix multiplication assignment (upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix multiplication assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix dense matrix multiplication assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix multiplication assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix dense matrix multiplication assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix multiplication assignment (upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix multiplication assignment (upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix multiplication assignment (upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix multiplication assignment (non-upper)
   {
      test_ = "Row-major/row-major StrictlyUpperMatrix sparse matrix multiplication assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix multiplication assignment (non-upper)
   {
      test_ = "Row-major/column-major StrictlyUpperMatrix sparse matrix multiplication assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major dense matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major dense matrix multiplication assignment (upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix multiplication assignment (upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix multiplication assignment (upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix multiplication assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix dense matrix multiplication assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix multiplication assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix dense matrix multiplication assignment (non-upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix multiplication assignment (upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix multiplication assignment (upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix multiplication assignment (upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != -5 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0 -5 )\n( 0  0  5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix multiplication assignment (non-upper)
   {
      test_ = "Column-major/row-major StrictlyUpperMatrix sparse matrix multiplication assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix multiplication assignment (non-upper)
   {
      test_ = "Column-major/column-major StrictlyUpperMatrix sparse matrix multiplication assignment (non-upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -1;
      mat(0,2) = -2;
      mat(1,2) =  3;
      mat(2,0) =  4;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of all StrictlyUpperMatrix (self-)scaling operations.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all available ways to scale an instance of the
// StrictlyUpperMatrix specialization. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void DenseTest::testScaling()
{
   //=====================================================================================
   // Row-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M*=s)";

      UT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      upper *= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M*s)";

      UT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      upper = upper * 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=s*M)";

      UT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      upper = 2 * upper;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M/=s)";

      UT upper( 3UL );
      upper(0,1) =  2;
      upper(0,2) = -4;
      upper(1,2) =  6;

      upper /= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Row-major self-scaling (M=M/s)";

      UT upper( 3UL );
      upper(0,1) =  2;
      upper(0,2) = -4;
      upper(1,2) =  6;

      upper = upper / 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major StrictlyUpperMatrix::scale()
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::scale()";

      // Initialization check
      UT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the matrix
      upper.scale( 2 );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      upper.scale( 0.5 );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Row-major StrictlyUpperMatrix::scale() (complex)";

      using blaze::complex;

      blaze::StrictlyUpperMatrix< blaze::DynamicMatrix<complex<float>,blaze::rowMajor> > upper( 2UL );
      upper(0,1) = complex<float>( 2.0F, 0.0F );

      upper.scale( complex<float>( 3.0F, 0.0F ) );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != complex<float>( 0.0F, 0.0F ) || upper(0,1) != complex<float>( 6.0F, 0.0F ) ||
          upper(1,0) != complex<float>( 0.0F, 0.0F ) || upper(1,1) != complex<float>( 0.0F, 0.0F ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( (0,0) (6,0)\n(0,0) (0,0) )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M*=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M*=s)";

      OUT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      upper *= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M*s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=M*s)";

      OUT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      upper = upper * 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=s*M)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=s*M)";

      OUT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      upper = 2 * upper;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M/=s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M/=s)";

      OUT upper( 3UL );
      upper(0,1) =  2;
      upper(0,2) = -4;
      upper(1,2) =  6;

      upper /= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major self-scaling (M=M/s)
   //=====================================================================================

   {
      test_ = "Column-major self-scaling (M=M/s)";

      OUT upper( 3UL );
      upper(0,1) =  2;
      upper(0,2) = -4;
      upper(1,2) =  6;

      upper = upper / 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Failed self-scaling operation\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major StrictlyUpperMatrix::scale()
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::scale()";

      // Initialization check
      OUT upper( 3UL );
      upper(0,1) =  1;
      upper(0,2) = -2;
      upper(1,2) =  3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the matrix
      upper.scale( 2 );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -4 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  6 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  2 -4 )\n( 0  0  6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the matrix
      upper.scale( 0.5 );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 1 || upper(0,2) != -2 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  1 -2 )\n( 0  0  3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "Column-major StrictlyUpperMatrix::scale() (complex)";

      using blaze::complex;

      blaze::StrictlyUpperMatrix< blaze::DynamicMatrix<complex<float>,blaze::columnMajor> > upper( 2UL );
      upper(0,1) = complex<float>( 2.0F, 0.0F );

      upper.scale( complex<float>( 3.0F, 0.0F ) );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != complex<float>( 0.0F, 0.0F ) || upper(0,1) != complex<float>( 6.0F, 0.0F ) ||
          upper(1,0) != complex<float>( 0.0F, 0.0F ) || upper(1,1) != complex<float>( 0.0F, 0.0F ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( (0,0) (6,0)\n(0,0) (0,0) )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StrictlyUpperMatrix function call operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the function call operator
// of the StrictlyUpperMatrix specialization. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void DenseTest::testFunctionCall()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::operator()";

      UT upper( 3UL );

      // Writing the element (1,2)
      upper(1,2) = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the element (0,1)
      upper(0,1) = upper(1,2);

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Adding to the element (0,2)
      upper(0,2) += 3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 3 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtracting from the element (0,1)
      upper(0,1) -= 4;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  3 )\n( 0  0  2 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplying the element (1,2)
      upper(1,2) *= -3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -6 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  3 )\n( 0  0 -6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Dividing the element (1,2)
      upper(1,2) /= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  3 )\n( 0  0 -3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to write the element (1,1)
      try {
         upper(1,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to diagonal matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      // Trying to write the element (2,1)
      try {
         upper(2,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to lower matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::operator()";

      OUT upper( 3UL );

      // Writing the element (1,2)
      upper(1,2) = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the element (0,1)
      upper(0,1) = upper(1,2);

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Adding to the element (0,2)
      upper(0,2) += 3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 3 )\n( 0 0 2 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtracting from the element (0,1)
      upper(0,1) -= 4;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  3 )\n( 0  0  2 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplying the element (1,2)
      upper(1,2) *= -3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -6 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  3 )\n( 0  0 -6 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Dividing the element (1,2)
      upper(1,2) /= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  3 )\n( 0  0 -3 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to write the element (1,1)
      try {
         upper(1,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to diagonal matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      // Trying to write the element (2,1)
      try {
         upper(2,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to lower matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StrictlyUpperMatrix iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testIterator()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      typedef UT::Iterator       Iterator;
      typedef UT::ConstIterator  ConstIterator;

      UT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Row-major Iterator/ConstIterator conversion";

         ConstIterator it( begin( upper, 1UL ) );

         if( it == end( upper, 1UL ) || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th row via Iterator
      {
         test_ = "Row-major Iterator subtraction";

         const size_t number( end( upper, 0UL ) - begin( upper, 0UL ) );

         if( number != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via ConstIterator
      {
         test_ = "Row-major ConstIterator subtraction";

         const size_t number( cend( upper, 1UL ) - cbegin( upper, 1UL ) );

         if( number != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Row-major read-only access via ConstIterator";

         ConstIterator it ( cbegin( upper, 0UL ) );
         ConstIterator end( cend( upper, 0UL ) );

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 3UL + it;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Scalar/iterator addition failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to upper elements via Iterator
      {
         test_ = "Row-major assignment to upper elements via Iterator";

         Iterator it = begin( upper, 0UL );
         ++it;
         *it = 2;
         ++it;
         *it = -2;

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -2 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2 -2 )\n( 0  0  0 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to diagonal elements via Iterator
      {
         test_ = "Row-major assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing assignment to lower elements via Iterator
      {
         test_ = "Row-major assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL );
            *it = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing addition assignment to upper elements via Iterator
      {
         test_ = "Row-major addition assignment to upper elements via Iterator";

         Iterator it = begin( upper, 0UL );
         ++it;
         *it += 2;
         ++it;
         *it += -2;

         if( upper(0,0) != 0 || upper(0,1) != 4 || upper(0,2) != -4 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  4 -4 )\n( 0  0  0 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment to diagonal elements via Iterator
      {
         test_ = "Row-major addition assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL ) + 1UL;
            *it += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing addition assignment to lower elements via Iterator
      {
         test_ = "Row-major addition assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 2UL );
            *it += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing subtraction assignment to upper elements via Iterator
      {
         test_ = "Row-major subtraction assignment to upper elements via Iterator";

         Iterator it = begin( upper, 0UL );
         ++it;
         *it -= 2;
         ++it;
         *it -= -2;

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -2 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2 -2 )\n( 0  0  0 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment to diagonal elements via Iterator
      {
         test_ = "Row-major subtraction assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 2UL ) + 2UL;
            *it -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing subtraction assignment to lower elements via Iterator
      {
         test_ = "Row-major subtraction assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL );
            *it -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing multiplication assignment to upper elements via Iterator
      {
         test_ = "Row-major multiplication assignment to upper elements via Iterator";

         Iterator it = begin( upper, 0UL );
         ++it;
         *it *= 2;
         ++it;
         *it *= 2;

         if( upper(0,0) != 0 || upper(0,1) != 4 || upper(0,2) != -4 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  4 -4 )\n( 0  0  0 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment to diagonal elements via Iterator
      {
         test_ = "Row-major multiplication assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing multiplication assignment to lower elements via Iterator
      {
         test_ = "Row-major multiplication assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 2UL );
            *it *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing division assignment to upper elements via Iterator
      {
         test_ = "Row-major division assignment to upper elements via Iterator";

         Iterator it = begin( upper, 0UL );
         ++it;
         *it /= 2;
         ++it;
         *it /= 2;

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != -2 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) !=  0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2 -2 )\n( 0  0  0 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment to diagonal elements via Iterator
      {
         test_ = "Row-major division assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL ) + 1UL;
            *it /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing division assignment to lower elements via Iterator
      {
         test_ = "Row-major division assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL );
            *it /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      typedef OUT::Iterator       Iterator;
      typedef OUT::ConstIterator  ConstIterator;

      OUT upper( 3UL );
      upper(0,2) = 3;
      upper(1,2) = 2;

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Column-major Iterator/ConstIterator conversion";

         ConstIterator it( begin( upper, 1UL ) );

         if( it == end( upper, 1UL ) || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th column via Iterator
      {
         test_ = "Column-major Iterator subtraction";

         const size_t number( end( upper, 0UL ) - begin( upper, 0UL ) );

         if( number != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st column via ConstIterator
      {
         test_ = "Column-major ConstIterator subtraction";

         const size_t number( cend( upper, 1UL ) - cbegin( upper, 1UL ) );

         if( number != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Column-major read-only access via ConstIterator";

         ConstIterator it ( cbegin( upper, 2UL ) );
         ConstIterator end( cend( upper, 2UL ) );

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || *it != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         --it;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it == end || *it != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it--;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-decrement failed\n";
            throw std::runtime_error( oss.str() );
         }

         it += 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator addition assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it -= 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator subtraction assignment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it + 2UL;

         if( it == end || *it != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar addition failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = it - 2UL;

         if( it == end || *it != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator/scalar subtraction failed\n";
            throw std::runtime_error( oss.str() );
         }

         it = 3UL + it;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Scalar/iterator addition failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to upper elements via Iterator
      {
         test_ = "Column-major assignment to upper elements via Iterator";

         Iterator it = begin( upper, 2UL );
         *it = 2;
         ++it;
         *it = -2;

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) !=  2 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -2 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  0  2 )\n( 0  0 -2 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to diagonal elements via Iterator
      {
         test_ = "Column-major assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing assignment to lower elements via Iterator
      {
         test_ = "Column-major assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL ) + 1UL;
            *it = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing addition assignment to upper elements via Iterator
      {
         test_ = "Column-major addition assignment to upper elements via Iterator";

         Iterator it = begin( upper, 2UL );
         *it += 2;
         ++it;
         *it += -2;

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) !=  4 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -4 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  0  4 )\n( 0  0 -4 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment to diagonal elements via Iterator
      {
         test_ = "Column-major addition assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL ) + 1UL;
            *it += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing addition assignment to lower elements via Iterator
      {
         test_ = "Column-major addition assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL ) + 2UL;
            *it += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing subtraction assignment to upper elements via Iterator
      {
         test_ = "Column-major subtraction assignment to upper elements via Iterator";

         Iterator it = begin( upper, 2UL );
         *it -= 2;
         ++it;
         *it -= -2;

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) !=  2 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -2 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  0  2 )\n( 0  0 -2 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment to diagonal elements via Iterator
      {
         test_ = "Column-major subtraction assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 2UL ) + 2UL;
            *it -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing subtraction assignment to lower elements via Iterator
      {
         test_ = "Column-major subtraction assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL ) + 1UL;
            *it -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing multiplication assignment to upper elements via Iterator
      {
         test_ = "Column-major multiplication assignment to upper elements via Iterator";

         Iterator it = begin( upper, 2UL );
         *it *= 2;
         ++it;
         *it *= 2;

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) !=  4 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -4 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  0  4 )\n( 0  0 -4 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment to diagonal elements via Iterator
      {
         test_ = "Column-major multiplication assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing multiplication assignment to lower elements via Iterator
      {
         test_ = "Column-major multiplication assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL ) + 2UL;
            *it *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing division assignment to upper elements via Iterator
      {
         test_ = "Column-major division assignment to upper elements via Iterator";

         Iterator it = begin( upper, 2UL );
         *it /= 2;
         ++it;
         *it /= 2;

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) !=  2 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -2 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  0  2 )\n( 0  0 -2 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment to diagonal elements via Iterator
      {
         test_ = "Column-major division assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 1UL ) + 1UL;
            *it /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing division assignment to lower elements via Iterator
      {
         test_ = "Column-major division assignment to lower elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL ) + 1UL;
            *it /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to lower matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c nonZeros() member function of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c nonZeros() member function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testNonZeros()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::nonZeros()";

      // Empty matrix
      {
         UT upper( 3UL );

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 0UL );
         checkNonZeros( upper, 0UL, 0UL );
         checkNonZeros( upper, 1UL, 0UL );
         checkNonZeros( upper, 2UL, 0UL );

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Partially filled matrix
      {
         UT upper( 3UL );
         upper(0,1) = 2;
         upper(0,2) = 3;

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 2UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 0UL );
         checkNonZeros( upper, 2UL, 0UL );

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2  3 )\n( 0  0 -5 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Fully filled matrix
      {
         UT upper( 3UL );
         upper(0,1) =  2;
         upper(0,2) =  3;
         upper(1,2) = -5;

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 3UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 0UL );

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) !=  3 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -5 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2  3 )\n( 0  0 -5 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::nonZeros()";

      // Empty matrix
      {
         OUT upper( 3UL );

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 0UL );
         checkNonZeros( upper, 0UL, 0UL );
         checkNonZeros( upper, 1UL, 0UL );
         checkNonZeros( upper, 2UL, 0UL );

         if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Partially filled matrix
      {
         OUT upper( 3UL );
         upper(0,1) = 2;
         upper(0,2) = 3;

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 2UL );
         checkNonZeros( upper, 0UL, 0UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 1UL );

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2  3 )\n( 0  0  0 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Fully filled matrix
      {
         OUT upper( 3UL );
         upper(0,1) =  2;
         upper(0,2) =  3;
         upper(1,2) = -5;

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 3UL );
         checkNonZeros( upper, 0UL, 0UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );

         if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) !=  3 ||
             upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != -5 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 0  2  3 )\n( 0  0 -5 )\n( 0  0  0 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reset() member function of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reset() member function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testReset()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::reset()";

      // Initialization check
      UT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 3 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting an upper element
      reset( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a diagonal element
      reset( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a lower element
      reset( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting row 1
      reset( upper, 1UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting the entire matrix
      reset( upper );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::reset()";

      // Initialization check
      OUT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 3 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting an upper element
      reset( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a diagonal element
      reset( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a lower element
      reset( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting column 1
      reset( upper, 1UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting the entire matrix
      reset( upper );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 0UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 0 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c clear() member function of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c clear() member function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testClear()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::clear()";

      // Initialization check
      UT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 3 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing an upper element
      clear( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a diagonal element
      clear( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a lower element
      clear( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing the matrix
      clear( upper );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::clear()";

      // Initialization check
      OUT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 3 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing an upper element
      clear( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a diagonal element
      clear( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a lower element
      clear( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 0 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing the matrix
      clear( upper );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c resize() member function of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c resize() member function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testResize()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::resize()";

      // Initialization check
      UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Resizing to 2x2
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );

      if( upper(0,0) != 0 || upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 x )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 4x4 and preserving the elements
      upper(0,1) = 2;
      upper.resize( 4UL, true );

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkCapacity( upper, 16UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ||
          upper(3,0) != 0 || upper(3,1) != 0 || upper(3,2) != 0 || upper(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 x x )\n( 0 0 x x )\n( 0 0 0 x )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 2x2
      upper(1,2) = 4;
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 0UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 0x0
      upper.resize( 0UL );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::resize()";

      // Initialization check
      OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Resizing to 2x2
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );

      if( upper(0,0) != 0 || upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 x )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 4x4 and preserving the elements
      upper(0,1) = 2;
      upper.resize( 4UL, true );

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkCapacity( upper, 16UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ||
          upper(3,0) != 0 || upper(3,1) != 0 || upper(3,2) != 0 || upper(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 x x )\n( 0 0 x x )\n( 0 0 0 x )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 2x2
      upper(1,2) = 4;
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 1UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 0x0
      upper.resize( 0UL );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c extend() member function of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c extend() member function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testExtend()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::extend()";

      // Initialization check
      UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Extending the size of the matrix to 2x2
      upper.extend( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );

      if( upper(0,0) != 0 || upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 x )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Extending to 4x4 and preserving the elements
      upper(0,1) = 2;
      upper.extend( 2UL, true );

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkCapacity( upper, 16UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ||
          upper(3,0) != 0 || upper(3,1) != 0 || upper(3,2) != 0 || upper(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 x x )\n( 0 0 x x )\n( 0 0 0 x )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::extend()";

      // Initialization check
      OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Extending the size of the matrix to 2x2
      upper.extend( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );

      if( upper(0,0) != 0 || upper(1,0) != 0 || upper(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 x )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Extending to 4x4 and preserving the elements
      upper(0,1) = 2;
      upper.extend( 2UL, true );

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkCapacity( upper, 16UL );

      if( upper(0,0) != 0 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ||
          upper(3,0) != 0 || upper(3,1) != 0 || upper(3,2) != 0 || upper(3,3) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Extending the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 2 x x )\n( 0 0 x x )\n( 0 0 0 x )\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reserve() member function of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reserve() member function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testReserve()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix::reserve()";

      // Initialization check
      UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Increasing the capacity of the matrix
      upper.reserve( 10UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 10UL );
      checkNonZeros( upper,  0UL );

      // Further increasing the capacity of the matrix
      upper.reserve( 20UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 20UL );
      checkNonZeros( upper,  0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix::reserve()";

      // Initialization check
      OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Increasing the capacity of the matrix
      upper.reserve( 10UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 10UL );
      checkNonZeros( upper,  0UL );

      // Further increasing the capacity of the matrix
      upper.reserve( 20UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 20UL );
      checkNonZeros( upper,  0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c swap() functionality of the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c swap() function of the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testSwap()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major StrictlyUpperMatrix swap";

      UT upper1( 2UL );
      upper1(0,1) = 2;

      UT upper2( 3UL );
      upper2(0,1) = 3;
      upper2(0,2) = 4;
      upper2(1,2) = 5;

      swap( upper1, upper2 );

      checkRows    ( upper1, 3UL );
      checkColumns ( upper1, 3UL );
      checkCapacity( upper1, 9UL );
      checkNonZeros( upper1, 3UL );
      checkNonZeros( upper1, 0UL, 2UL );
      checkNonZeros( upper1, 1UL, 1UL );
      checkNonZeros( upper1, 2UL, 0UL );

      if( upper1(0,0) != 0 || upper1(0,1) != 3 || upper1(0,2) != 4 ||
          upper1(1,0) != 0 || upper1(1,1) != 0 || upper1(1,2) != 5 ||
          upper1(2,0) != 0 || upper1(2,1) != 0 || upper1(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the first matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper1 << "\n"
             << "   Expected result:\n( 0 3 4 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      checkRows    ( upper2, 2UL );
      checkColumns ( upper2, 2UL );
      checkCapacity( upper2, 4UL );
      checkNonZeros( upper2, 1UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 0UL );

      if( upper2(0,0) != 0 || upper2(0,1) != 2 || upper2(1,0) != 0 || upper2(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the second matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 2 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major StrictlyUpperMatrix swap";

      OUT upper1( 2UL );
      upper1(0,1) = 2;

      OUT upper2( 3UL );
      upper2(0,1) = 3;
      upper2(0,2) = 4;
      upper2(1,2) = 5;

      swap( upper1, upper2 );

      checkRows    ( upper1, 3UL );
      checkColumns ( upper1, 3UL );
      checkCapacity( upper1, 9UL );
      checkNonZeros( upper1, 3UL );
      checkNonZeros( upper1, 0UL, 0UL );
      checkNonZeros( upper1, 1UL, 1UL );
      checkNonZeros( upper1, 2UL, 2UL );

      if( upper1(0,0) != 0 || upper1(0,1) != 3 || upper1(0,2) != 4 ||
          upper1(1,0) != 0 || upper1(1,1) != 0 || upper1(1,2) != 5 ||
          upper1(2,0) != 0 || upper1(2,1) != 0 || upper1(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the first matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper1 << "\n"
             << "   Expected result:\n( 0 3 4 )\n( 0 0 5 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      checkRows    ( upper2, 2UL );
      checkColumns ( upper2, 2UL );
      checkCapacity( upper2, 4UL );
      checkNonZeros( upper2, 1UL );
      checkNonZeros( upper2, 0UL, 0UL );
      checkNonZeros( upper2, 1UL, 1UL );

      if( upper2(0,0) != 0 || upper2(0,1) != 2 || upper2(1,0) != 0 || upper2(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the second matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 0 2 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isDefault() function with the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isDefault() function with the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testIsDefault()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major isDefault() function";

      // isDefault with 0x0 matrix
      {
         UT upper;

         if( isDefault( upper ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with default matrix
      {
         UT upper( 3UL );

         if( isDefault( upper(0,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default matrix
      {
         UT upper( 3UL );
         upper(0,1) = 1;

         if( isDefault( upper(0,1) ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major isDefault() function";

      // isDefault with 0x0 matrix
      {
         OUT upper;

         if( isDefault( upper ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with default matrix
      {
         OUT upper( 3UL );

         if( isDefault( upper(0,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default matrix
      {
         OUT upper( 3UL );
         upper(0,1) = 1;

         if( isDefault( upper(0,1) ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c submatrix() function with the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c submatrix() function with the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testSubmatrix()
{
   //=====================================================================================
   // Row-major general tests
   //=====================================================================================

   {
      test_ = "Row-major submatrix() function";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      if( sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << sm(1,1) << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }

      SMT::Iterator it = sm.begin(0UL);

      if( it == sm.end(0UL) || *it != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }

      sm(0,1) = -5;

      if( sm(0,0) != 0 || sm(0,1) != -5 ||
          sm(1,0) != 0 || sm(1,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -5 )\n( 0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( sm );

      if( sm(0,0) != 0 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major scalar assignment
   //=====================================================================================

   // ( 0 -4  7 -2 )      ( 0 12 12 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (scalar assignment test 1)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = 12;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 12 || sm(0,1) != 12 ||
          sm(1,0) !=  0 || sm(1,1) != 12 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 12 )\n(  0 12 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 12 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 12 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 12 -2 )\n"
                                     "( 0  0 12  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12 12 )
   // ( 0  0  0  1 )      ( 0  0  0 12 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (scalar assignment test 2)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = 12;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 12 || sm(0,3) != 12 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 12 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 12 12 )\n( 0  0  0 12 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 12 || upper(1,3) != 12 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 12 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 12 12 )\n"
                                     "( 0  0  0 12 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0  0  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (scalar assignment test 3)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 2UL, 0UL, 2UL, 2UL );
      sm = 12;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) != 0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0  0  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 0 );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  0;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  0;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 0 );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  0;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  0;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 4UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;
      mat.insert( 3UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 4UL );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 2UL );
      mat(0,1) = 12;
      mat(1,0) = 13;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 4UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;
      mat.insert( 3UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 4UL );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 0UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  0 )
   // ( 0  0  0  0 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 2UL );
      mat(0,1) = 12;
      mat(1,0) = 13;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major general tests
   //=====================================================================================

   {
      test_ = "Column-major submatrix() function";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(1,2) =  5;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      if( sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << sm(1,1) << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }

      SMT::Iterator it = sm.begin(1UL);

      if( it == sm.end(1UL) || *it != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: 5\n";
         throw std::runtime_error( oss.str() );
      }

      sm(0,1) = -5;

      if( sm(0,0) != 0 || sm(0,1) != -5 ||
          sm(1,0) != 0 || sm(1,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 -5 )\n( 0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0 -5 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( sm );

      if( sm(0,0) != 0 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major scalar assignment
   //=====================================================================================

   // ( 0 -4  7 -2 )      ( 0 12 12 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (scalar assignment test 1)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = 12;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 2UL );

      if( sm(0,0) != 12 || sm(0,1) != 12 ||
          sm(1,0) !=  0 || sm(1,1) != 12 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 12 )\n(  0 12 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 12 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 12 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 12 -2 )\n"
                                     "( 0  0 12  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12 12 )
   // ( 0  0  0  1 )      ( 0  0  0 12 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (scalar assignment test 2)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = 12;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 12 || sm(0,3) != 12 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 12 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 12 12 )\n( 0  0  0 12 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 12 || upper(1,3) != 12 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 12 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 12 12 )\n"
                                     "( 0  0  0 12 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0  0  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (scalar assignment test 3)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 2UL, 0UL, 2UL, 2UL );
      sm = 12;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 2UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0 0 )\n( 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) != 0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0  0  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 2UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 0 );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  0;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  0;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 2UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 0 );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  0;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  0;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 4UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;
      mat.insert( 3UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 2UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 4UL );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 2UL );
      mat(0,1) = 12;
      mat(1,0) = 13;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 12 15 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 17  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 1)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 4UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,1) = 17;
      mat.insert( 3UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 2UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  0 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  0 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  0 17 )\n(  0  0 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 12 15 -2 )\n"
                                     "( 0  0 17  0 )\n"
                                     "( 0  0  0  1 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 14 10 )
   // ( 0  0  0  1 )      ( 0  0  0 16 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 2)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 4UL );
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 0 || sm(0,1) != 0 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  0 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  0 14 10 )\n( 0  0  0 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 -2 )\n"
                                     "( 0  0 14 10 )\n"
                                     "( 0  0  0 16 )\n"
                                     "( 0  0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 3)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 -2 )      ( 0 -4  7 -2 )
   // ( 0  0  0  0 )  =>  ( 0  0 12  0 )
   // ( 0  0  0  1 )      ( 0 13  0  1 )
   // ( 0  0  0  0 )      ( 0  0  0  0 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 4)";

      typedef blaze::DenseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 2UL );
      mat(0,1) = 12;
      mat(1,0) = 13;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c row() function with the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c row() function with the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testRow()
{
   //=====================================================================================
   // Row-major general tests
   //=====================================================================================

   {
      test_ = "Row-major row() function";

      typedef blaze::DenseRow<UT>  RT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row0 = row( upper, 0UL );

      if( row0[1] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << row0[1] << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      RT::Iterator it = row0.begin();

      if( it == row0.end() || *it != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }

      row0[1] = -5;

      if( row0[0] != 0 || row0[1] != -5 || row0[2] != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row0 << "\n"
             << "   Expected result:\n( 0 -5  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -5 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -5  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( row0 );

      if( row0[0] != 0 || row0[1] != 0 || row0[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row0 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0  0 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major scalar assignment
   //=====================================================================================

   {
      test_ = "Row-major row() function (scalar assignment test)";

      typedef blaze::DenseRow<UT>  RT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = 8;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != 8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 0 8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 8 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  8 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major row() function (dense vector assignment test 1)";

      typedef blaze::DenseRow<UT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  0 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0 -2 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  1 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major row() function (dense vector assignment test 2)";

      typedef blaze::DenseRow<UT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[1] =  1;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 9  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major row() function (dense vector assignment test 3)";

      typedef blaze::DenseRow<UT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[0] =  9;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major row() function (sparse vector assignment test 1)";

      typedef blaze::DenseRow<UT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 2UL );
      vec[2] = -2;
      vec.insert( 0UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  0 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0 -2 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  1 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major row() function (sparse vector assignment test 2)";

      typedef blaze::DenseRow<UT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 2UL );
      vec[1] =  1;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 9  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major row() function (sparse vector assignment test 3)";

      typedef blaze::DenseRow<UT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 2UL );
      vec[0] =  9;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major general tests
   //=====================================================================================

   {
      test_ = "Column-major row() function";

      typedef blaze::DenseRow<OUT>  RT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row0 = row( upper, 0UL );

      if( row0[1] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << row0[1] << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      RT::Iterator it = row0.begin();

      if( it == row0.end() || *it != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }

      row0[1] = -5;

      if( row0[0] != 0 || row0[1] != -5 || row0[2] != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row0 << "\n"
             << "   Expected result:\n( 0 -5  7 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -5 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -5  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( row0 );

      if( row0[0] != 0 || row0[1] != 0 || row0[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row0 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  0  0 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major scalar assignment
   //=====================================================================================

   {
      test_ = "Column-major row() function (scalar assignment test)";

      typedef blaze::DenseRow<OUT>  RT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = 8;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != 8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 0 8 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 8 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0  8 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major row() function (dense vector assignment test 1)";

      typedef blaze::DenseRow<OUT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  0 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0 -2 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  1 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major row() function (dense vector assignment test 2)";

      typedef blaze::DenseRow<OUT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[1] =  1;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 9  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major row() function (dense vector assignment test 3)";

      typedef blaze::DenseRow<OUT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[0] =  9;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major row() function (sparse vector assignment test 1)";

      typedef blaze::DenseRow<OUT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 2UL );
      vec[2] = -2;
      vec.insert( 0UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( row1[0] != 0 || row1[1] != 0 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  0 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -4  7 )\n( 0  0 -2 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 0  1 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major row() function (sparse vector assignment test 2)";

      typedef blaze::DenseRow<OUT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 2UL );
      vec[1] =  1;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -4  7 )
   // ( 0  0  0 )  =>  ( 9  0 -2 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major row() function (sparse vector assignment test 3)";

      typedef blaze::DenseRow<OUT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 2UL );
      vec[0] =  9;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c column() function with the StrictlyUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c column() function with the StrictlyUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void DenseTest::testColumn()
{
   //=====================================================================================
   // Row-major general tests
   //=====================================================================================

   {
      test_ = "Row-major column() function";

      typedef blaze::DenseColumn<UT>  CT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      if( col1[0] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[0] << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      CT::Iterator it = col1.begin();

      if( it == col1.end() || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      col1[0] = -5;

      if( col1[0] != -5 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -5  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -5 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -5  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( col1 );

      if( col1[0] != 0 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 7 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major scalar assignment
   //=====================================================================================

   {
      test_ = "Row-major column() function (scalar assignment test)";

      typedef blaze::DenseColumn<UT>  CT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = 8;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( col1[0] != 8 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 8 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 8 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 8 7 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major column() function (dense vector assignment test 1)";

      typedef blaze::DenseColumn<UT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( col1[0] != -2 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  1  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major column() function (dense vector assignment test 2)";

      typedef blaze::DenseColumn<UT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;
      vec[1] =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  9  0 )
   {
      test_ = "Row-major column() function (dense vector assignment test 3)";

      typedef blaze::DenseColumn<UT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;
      vec[2] =  9;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major column() function (sparse vector assignment test 1)";

      typedef blaze::DenseColumn<UT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 2UL );
      vec[0] = -2;
      vec.insert( 2UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 0UL );
      checkNonZeros( upper, 2UL, 0UL );

      if( col1[0] != -2 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  1  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Row-major column() function (sparse vector assignment test 2)";

      typedef blaze::DenseColumn<UT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 2UL );
      vec[0] = -2;
      vec[1] =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  9  0 )
   {
      test_ = "Row-major column() function (sparse vector assignment test 3)";

      typedef blaze::DenseColumn<UT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 2UL );
      vec[0] = -2;
      vec[2] =  9;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major general tests
   //=====================================================================================

   {
      test_ = "Column-major column() function";

      typedef blaze::DenseColumn<OUT>  CT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      if( col1[0] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[0] << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      CT::Iterator it = col1.begin();

      if( it == col1.end() || *it != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << *it << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      col1[0] = -5;

      if( col1[0] != -5 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -5  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -5 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0  -5  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( col1 );

      if( col1[0] != 0 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 0 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 0 7 )\n( 0 0 0 )\n(  0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major scalar assignment
   //=====================================================================================

   {
      test_ = "Column-major column() function (scalar assignment test)";

      typedef blaze::DenseColumn<OUT>  CT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = 8;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( col1[0] != 8 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 8 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != 8 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) != 0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n(  0 8 7 )\n( 0 0 0 )\n( 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major column() function (dense vector assignment test 1)";

      typedef blaze::DenseColumn<OUT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( col1[0] != -2 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  1  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major column() function (dense vector assignment test 2)";

      typedef blaze::DenseColumn<OUT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;
      vec[1] =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  9  0 )
   {
      test_ = "Column-major column() function (dense vector assignment test 3)";

      typedef blaze::DenseColumn<OUT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;
      vec[2] =  9;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse vector assignment
   //=====================================================================================

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major column() function (sparse vector assignment test 1)";

      typedef blaze::DenseColumn<OUT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 2UL );
      vec[0] = -2;
      vec.insert( 2UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 0UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( col1[0] != -2 || col1[1] != 0 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 0 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  0 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 0 -2  7 )\n( 0  0  0 )\n( 0  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  1  0 )
   // ( 0  0  0 )      ( 0  0  0 )
   {
      test_ = "Column-major column() function (sparse vector assignment test 2)";

      typedef blaze::DenseColumn<OUT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 2UL );
      vec[0] = -2;
      vec[1] =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 0 -4  7 )      ( 0 -2  7 )
   // ( 0  0  0 )  =>  ( 0  0  0 )
   // ( 0  0  0 )      ( 0  9  0 )
   {
      test_ = "Column-major column() function (sparse vector assignment test 3)";

      typedef blaze::DenseColumn<OUT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 2UL );
      vec[0] = -2;
      vec[2] =  9;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************

} // namespace strictlyuppermatrix

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
   std::cout << "   Running StrictlyUpperMatrix dense test..." << std::endl;

   try
   {
      RUN_STRICTLYUPPERMATRIX_DENSE_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during StrictlyUpperMatrix dense test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
