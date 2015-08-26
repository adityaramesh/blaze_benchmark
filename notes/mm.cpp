template< typename MT3    // Type of the left-hand side target matrix
        , typename MT4    // Type of the left-hand side matrix operand
        , typename MT5 >  // Type of the right-hand side matrix operand
static inline typename EnableIf< UseVectorizedDefaultKernel<MT3,MT4,MT5> >::Type
   selectLargeAssignKernel( DenseMatrix<MT3,false>& C, const MT4& A, const MT5& B )
{
   typedef IntrinsicTrait<ElementType>  IT;

   const size_t M( A.rows()    );
   const size_t N( B.columns() );
   const size_t K( A.columns() );

   const size_t iblock(  64UL );
   const size_t jblock( 128UL );
   const size_t kblock( 128UL );

   // Tile j-loop by 128?
   for( size_t jj=0UL; jj<N; jj+=jblock )
   {
      const size_t jend(jj+jblock);

      // Tile i-loop by 64?
      for( size_t ii=0UL; ii<M; ii+=iblock )
      {
         const size_t iend(ii+iblock);

	 // Clear C before accumulating values. As a possible optimization, we
	 // could do the following:
	 // (1) Provide a "fast assignment" option that assumes that C is
	 // already clear.
	 // (2) Otherwise, peel off an iteration from the actual computation,
	 // and use stores without loads.
         for( size_t i=ii; i<iend; ++i ) {
            for( size_t j=jj; j<jend; ++j ) {
               reset( (~C)(i,j) );
            }
         }

	 // Tile k-loop by 128?
         for( size_t kk=0UL; kk<K; kk+=kblock )
         {
            const size_t ktmp(kk+kblock);

            size_t j( jj );

	    // Unroll j-loop by 4, using j, j1, j2, j3.
            for( ; (j+IT::size*3UL) < jend; j+=IT::size*4UL )
            {
               const size_t j1( j+IT::size     );
               const size_t j2( j+IT::size*2UL );
               const size_t j3( j+IT::size*3UL );

               size_t i( ii );

	       // Unroll i-loop by 2.
               for( ; (i+2UL) <= iend; i+=2UL )
               {
                  const size_t kbegin(kk);
                  const size_t kend  (ktmp);

		  /*
		  ** Block of C that is loaded:
		  ** ( **** ... )
		  ** ( **** ... )
		  ** ( ...  ... )
		  ** ( ...  ... )
		  */

		  /*
		  ** Note: isn't this code highly suboptimal for AVX? With AVX,
		  ** we have 32 registers from YMM0--YMM31. This loop uses only
		  ** loads 8 values of C at a time. Doesn't this make highly
		  ** suboptimal usage of registers?
		  */
                  IntrinsicType xmm1( (~C).load(i    ,j ) );
                  IntrinsicType xmm2( (~C).load(i    ,j1) );
                  IntrinsicType xmm3( (~C).load(i    ,j2) );
                  IntrinsicType xmm4( (~C).load(i    ,j3) );
                  IntrinsicType xmm5( (~C).load(i+1UL,j ) );
                  IntrinsicType xmm6( (~C).load(i+1UL,j1) );
                  IntrinsicType xmm7( (~C).load(i+1UL,j2) );
                  IntrinsicType xmm8( (~C).load(i+1UL,j3) );

                  for( size_t k=kbegin; k<kend; ++k ) {
		     /*
		     ** Parts of A and B that are loaded:
		     ** ( *   ... ) ( * * * * ... )
		     ** ( *   ... ) ( ...     ... )
		     ** ( ... ... ) ( ...     ... )
		     */
                     const IntrinsicType a1( set( A(i    ,k) ) );
                     const IntrinsicType a2( set( A(i+1UL,k) ) );
                     const IntrinsicType b1( B.load(k,j ) );
                     const IntrinsicType b2( B.load(k,j1) );
                     const IntrinsicType b3( B.load(k,j2) );
                     const IntrinsicType b4( B.load(k,j3) );
                     xmm1 = xmm1 + a1 * b1;
                     xmm2 = xmm2 + a1 * b2;
                     xmm3 = xmm3 + a1 * b3;
                     xmm4 = xmm4 + a1 * b4;
                     xmm5 = xmm5 + a2 * b1;
                     xmm6 = xmm6 + a2 * b2;
                     xmm7 = xmm7 + a2 * b3;
                     xmm8 = xmm8 + a2 * b4;
                  }

                  (~C).store( i    , j , xmm1 );
                  (~C).store( i    , j1, xmm2 );
                  (~C).store( i    , j2, xmm3 );
                  (~C).store( i    , j3, xmm4 );
                  (~C).store( i+1UL, j , xmm5 );
                  (~C).store( i+1UL, j1, xmm6 );
                  (~C).store( i+1UL, j2, xmm7 );
                  (~C).store( i+1UL, j3, xmm8 );
               }

	       // Remainder i-loop within main j-loop.
               if( i < iend )
               {
                  const size_t kbegin(kk);
                  const size_t kend  (ktmp);

		  /*
		  ** Block of C that is loaded:
		  ** ( *   ... )
		  ** ( *   ... )
		  ** ( *   ... )
		  ** ( *   ... )
		  ** ( ... ... )
		  */
                  IntrinsicType xmm1( (~C).load(i,j ) );
                  IntrinsicType xmm2( (~C).load(i,j1) );
                  IntrinsicType xmm3( (~C).load(i,j2) );
                  IntrinsicType xmm4( (~C).load(i,j3) );

                  for( size_t k=kbegin; k<kend; ++k ) {
		     /*
		     ** Parts of A and B that are loaded:
		     ** ( *   ... ) ( * * * * ... )
		     ** ( ... ... ) ( ...     ... )
		     ** ( ... ... ) ( ...     ... )
		     */
                     const IntrinsicType a1( set( A(i,k) ) );
                     xmm1 = xmm1 + a1 * B.load(k,j );
                     xmm2 = xmm2 + a1 * B.load(k,j1);
                     xmm3 = xmm3 + a1 * B.load(k,j2);
                     xmm4 = xmm4 + a1 * B.load(k,j3);
                  }

                  (~C).store( i, j , xmm1 );
                  (~C).store( i, j1, xmm2 );
                  (~C).store( i, j2, xmm3 );
                  (~C).store( i, j3, xmm4 );
               }
            }

	    // Unrolled remainder j-loop.
            for( ; (j+IT::size) < jend; j+=IT::size*2UL )
            {
               const size_t j1( j+IT::size );

               size_t i( ii );

               for( ; (i+4UL) <= iend; i+=4UL )
               {
                  const size_t kbegin(kk);
                  const size_t kend  (ktmp);

		  /*
		  ** Part of C that is loaded:
		  ** ( **  ... )
		  ** ( **  ... )
		  ** ( **  ... )
		  ** ( **  ... )
		  ** ( ... ... )
		  */
                  IntrinsicType xmm1( (~C).load(i    ,j ) );
                  IntrinsicType xmm2( (~C).load(i    ,j1) );
                  IntrinsicType xmm3( (~C).load(i+1UL,j ) );
                  IntrinsicType xmm4( (~C).load(i+1UL,j1) );
                  IntrinsicType xmm5( (~C).load(i+2UL,j ) );
                  IntrinsicType xmm6( (~C).load(i+2UL,j1) );
                  IntrinsicType xmm7( (~C).load(i+3UL,j ) );
                  IntrinsicType xmm8( (~C).load(i+3UL,j1) );

                  for( size_t k=kbegin; k<kend; ++k ) {
		     /*
		     ** Parts of A and B that are loaded:
		     ** ( *   ... ) ( * * ... )
		     ** ( *   ... ) ( ... ... )
		     ** ( *   ... ) ( ... ... )
		     ** ( *   ... )
		     ** ( ... ... )
		     **
		     ** Question: why are we loading four elements of A and two
		     ** elements of B, unlike in the main j-loop where it was
		     ** the other way around? Because this j-loop is unrolled by
		     ** two instead of four.
		     */
                     const IntrinsicType a1( set( A(i    ,k) ) );
                     const IntrinsicType a2( set( A(i+1UL,k) ) );
                     const IntrinsicType a3( set( A(i+2UL,k) ) );
                     const IntrinsicType a4( set( A(i+3UL,k) ) );
                     const IntrinsicType b1( B.load(k,j ) );
                     const IntrinsicType b2( B.load(k,j1) );
                     xmm1 = xmm1 + a1 * b1;
                     xmm2 = xmm2 + a1 * b2;
                     xmm3 = xmm3 + a2 * b1;
                     xmm4 = xmm4 + a2 * b2;
                     xmm5 = xmm5 + a3 * b1;
                     xmm6 = xmm6 + a3 * b2;
                     xmm7 = xmm7 + a4 * b1;
                     xmm8 = xmm8 + a4 * b2;
                  }

                  (~C).store( i    , j , xmm1 );
                  (~C).store( i    , j1, xmm2 );
                  (~C).store( i+1UL, j , xmm3 );
                  (~C).store( i+1UL, j1, xmm4 );
                  (~C).store( i+2UL, j , xmm5 );
                  (~C).store( i+2UL, j1, xmm6 );
                  (~C).store( i+3UL, j , xmm7 );
                  (~C).store( i+3UL, j1, xmm8 );
               }

	       // Unrolled remainder i-loop in unrolled remainder j-loop.
               for( ; (i+2UL) <= iend; i+=2UL )
               {
                  const size_t kbegin(kk);
                  const size_t kend  (ktmp);

		  /*
		  ** Part of C that is loaded:
		  ** ( **  ... )
		  ** ( **  ... )
		  ** ( ... ... )
		  ** ( ... ... )
		  ** ( ... ... )
		  */
                  IntrinsicType xmm1( (~C).load(i    ,j ) );
                  IntrinsicType xmm2( (~C).load(i    ,j1) );
                  IntrinsicType xmm3( (~C).load(i+1UL,j ) );
                  IntrinsicType xmm4( (~C).load(i+1UL,j1) );

		  // Note that the k-loop isn't unrolled. Is this a possible
		  // optimization opportunity?
                  for( size_t k=kbegin; k<kend; ++k ) {
		     /*
		     ** Parts of A and B that are loaded:
		     ** ( *   ... ) ( * * ... )
		     ** ( *   ... ) ( ... ... )
		     ** ( ... ... ) ( ... ... )
		     */
                     const IntrinsicType a1( set( A(i    ,k) ) );
                     const IntrinsicType a2( set( A(i+1UL,k) ) );
                     const IntrinsicType b1( B.load(k,j ) );
                     const IntrinsicType b2( B.load(k,j1) );
                     xmm1 = xmm1 + a1 * b1;
                     xmm2 = xmm2 + a1 * b2;
                     xmm3 = xmm3 + a2 * b1;
                     xmm4 = xmm4 + a2 * b2;
                  }

                  (~C).store( i    , j , xmm1 );
                  (~C).store( i    , j1, xmm2 );
                  (~C).store( i+1UL, j , xmm3 );
                  (~C).store( i+1UL, j1, xmm4 );
               }

	       // Remainder i-loop within remainder j-loop.
               if( i < iend )
               {
                  const size_t kbegin(kk);
                  const size_t kend  (ktmp);

		  /*
		  ** Part of C that is loaded:
		  ** ( **  ... )
		  ** ( ... ... )
		  */
                  IntrinsicType xmm1( (~C).load(i,j ) );
                  IntrinsicType xmm2( (~C).load(i,j1) );

		  // Again, the remainder k-loop isn't unrolled.
                  for( size_t k=kbegin; k<kend; ++k ) {
		     /*
		     ** Parts of A and B that are loaded:
		     ** ( *   ... ) ( * * ... )
		     ** ( ... ... ) ( ... ... )
		     */
                     const IntrinsicType a1( set( A(i,k) ) );
                     xmm1 = xmm1 + a1 * B.load(k,j );
                     xmm2 = xmm2 + a1 * B.load(k,j1);
                  }

                  (~C).store( i, j , xmm1 );
                  (~C).store( i, j1, xmm2 );
               }
            }

	    // Remainder j-loop (after the unrolled remainder j-loop). The
	    // previous unroll factor was 2, so we only have one j-iteration
	    // left.
            if( j < jend )
            {
	       // Remainder i-loop within remainder j-loop.
               for( size_t i=ii; i<iend; ++i )
               {
                  const size_t kbegin(kk);
                  const size_t kend  (ktmp);

                  IntrinsicType xmm1( (~C).load(i,j) );

		  // Remainder k-loop within remainder i-loop. Again, this loop
		  // isn't unrolled, so we may be able to optimize this further.
                  for( size_t k=kbegin; k<kend; ++k ) {
                     const IntrinsicType a1( set( A(i,k) ) );
                     xmm1 = xmm1 + a1 * B.load(k,j);
                  }

                  (~C).store( i, j, xmm1 );
               }
            }
         }
      }
   }
}

