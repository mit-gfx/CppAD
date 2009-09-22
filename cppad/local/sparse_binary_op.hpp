/* $Id$ */
# ifndef CPPAD_SPARSE_BINARY_OP_INCLUDED
# define CPPAD_SPARSE_BINARY_OP_INCLUDED
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-09 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the 
                    Common Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */
CPPAD_BEGIN_NAMESPACE

/*!
\file sparse_binary_op.hpp
Forward and reverse mode sparsity patterns for binary operators.
*/


/*!
Forward mode Jacobian sparsity pattern for all binary operators. 

The C++ source code corresponding to a binary operation has the form
\verbatim
	z = fun(x, y)
\endverbatim
where fun is a C++ binary function and both x and y are variables, 
or it has the form
\verbatim
	z = x op y
\endverbatim
where op is a C++ binary unary operator and both x and y are variables.

\param i_z
variable index corresponding to the result for this operation; 
i.e. the from node index in sparsity corresponding to z. 

\param arg
\a arg[0]
variable index corresponding to the left operand for this operator;
i.e. the from node index in sparsity corresponding to x.
\n
\n arg[1]
variable index corresponding to the right operand for this operator;
i.e. the from node index in sparsity corresponding to y.

\param sparsity
\b Input: 
The from node with index \a arg[0] in \a sparsity
contains the sparsity bit pattern for x.
This identifies which of the independent variables the variable x
depends on. 
\n
\n
\b Input: 
The from node with index \a arg[1] in \a sparsity
contains the sparsity bit pattern for y.
This identifies which of the independent variables the variable y
depends on. 
\n
\n
\b Output: 
The from node with index \a i_z in \a sparsity
contains the sparsity bit pattern for z.
This identifies which of the independent variables the variable z
depends on. 

\par Checked Assertions:
\li \a arg[0] < \a i_z 
\li \a arg[1] < \a i_z 
*/


inline void forward_sparse_jacobian_binary_op(
	size_t            i_z           ,
	const size_t*     arg           ,
	vector_pack&      sparsity      )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( arg[0] < i_z );
	CPPAD_ASSERT_UNKNOWN( arg[1] < i_z );

	sparsity.binary_union(i_z, arg[0], arg[1], sparsity);

	return;
}	

/*!
Reverse mode Jacobian sparsity pattern for all binary operators. 

The C++ source code corresponding to a unary operation has the form
\verbatim
	z = fun(x, y)
\endverbatim
where fun is a C++ unary function and x and y are variables, 
or it has the form
\verbatim
	z = x op y
\endverbatim
where op is a C++ bianry operator and x and y are variables.

This routine is given the sparsity patterns
for a function G(z, y, x, ... )
and it uses them to compute the sparsity patterns for 
\verbatim
	H( y, x, w , u , ... ) = G[ z(x,y) , y , x , w , u , ... ]
\endverbatim

\tparam Pack
is the type used to pack the sparsity pattern bit values; i.e.,
there is more that one bit per Pack value.

\param i_z
variable index corresponding to the result for this operation; 
i.e., the from node index in sparsity pattern corresponding to z.

\param arg
\a arg[0]
variable index corresponding to the left operand for this operator;
i.e., the from node index in sparsity pattern corresponding to x.

\n
\n arg[1]
variable index corresponding to the right operand for this operator;
i.e., the from node index in sparsity pattern corresponding to y.

\param sparsity
The (EDIT THIS) connections in \a sparsity for the
from node with index \a i_z are the sparsity pattern for z 
and corresponding ot the function G.
\n
\n
The (EDIT THIS) connections in \a sparsity for the 
from node with index \a arg[0] are the sparsity pattern for x.
On input, they correspond to the function G,
and on output they correspond to H.
\n
\n
The (EDIT THIS) connections in \a sparsity for the 
from node with index \a arg[1] are the sparsity pattern for y.
On input, they correspond to the function G,
and on output they correspond to H.

\par Checked Assertions:
\li \a arg[0] < \a i_z 
\li \a arg[1] < \a i_z 
*/
inline void reverse_sparse_jacobian_binary_op(
	size_t              i_z           ,
	const size_t*       arg           ,
	vector_pack&        sparsity      )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( arg[0] < i_z );
	CPPAD_ASSERT_UNKNOWN( arg[1] < i_z );

	sparsity.binary_union(arg[0], arg[0], i_z, sparsity);
	sparsity.binary_union(arg[1], arg[1], i_z, sparsity);

	return;
}	

/*!
Reverse mode Hessian sparsity pattern for add and subtract operators. 

The C++ source code corresponding to a unary operation has the form
\verbatim
	z = x op y
\endverbatim
where op is + or - and x, y are variables.

\copydetails reverse_sparse_hessian_binary_op
*/
inline void reverse_sparse_hessian_addsub_op(
	size_t               i_z                ,
	const size_t*        arg                ,
	bool*                jac_reverse        ,
	vector_pack&         for_jac_sparsity   ,
	vector_pack&         rev_hes_sparsity   )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( arg[0] < i_z );
	CPPAD_ASSERT_UNKNOWN( arg[1] < i_z );

	rev_hes_sparsity.binary_union(arg[0], arg[0], i_z, rev_hes_sparsity);
	rev_hes_sparsity.binary_union(arg[1], arg[1], i_z, rev_hes_sparsity);

	jac_reverse[arg[0]] |= jac_reverse[i_z];
	jac_reverse[arg[1]] |= jac_reverse[i_z];

	return;
}	

/*!
Reverse mode Hessian sparsity pattern for multiplication operator. 

The C++ source code corresponding to a unary operation has the form
\verbatim
	z = x * y
\endverbatim
where x and y are variables.

\copydetails reverse_sparse_hessian_binary_op
*/
inline void reverse_sparse_hessian_mul_op(
	size_t               i_z                ,
	const size_t*        arg                ,
	bool*                jac_reverse        ,
	vector_pack&         for_jac_sparsity   ,
	vector_pack&         rev_hes_sparsity   )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( arg[0] < i_z );
	CPPAD_ASSERT_UNKNOWN( arg[1] < i_z );

	rev_hes_sparsity.binary_union(arg[0], arg[0], i_z, rev_hes_sparsity);
	rev_hes_sparsity.binary_union(arg[1], arg[1], i_z, rev_hes_sparsity);

	if( jac_reverse[i_z] )
	{	rev_hes_sparsity.binary_union(
			arg[0], arg[0], arg[1], for_jac_sparsity); 
		rev_hes_sparsity.binary_union(
			arg[1], arg[1], arg[0], for_jac_sparsity); 
	}

	jac_reverse[arg[0]] |= jac_reverse[i_z];
	jac_reverse[arg[1]] |= jac_reverse[i_z];
	return;
}	

/*!
Reverse mode Hessian sparsity pattern for division operator. 

The C++ source code corresponding to a unary operation has the form
\verbatim
	z = x / y
\endverbatim
where x and y are variables.

\copydetails reverse_sparse_hessian_binary_op
*/
inline void reverse_sparse_hessian_div_op(
	size_t               i_z                ,
	const size_t*        arg                ,
	bool*                jac_reverse        ,
	vector_pack&         for_jac_sparsity   ,
	vector_pack&         rev_hes_sparsity   )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( arg[0] < i_z );
	CPPAD_ASSERT_UNKNOWN( arg[1] < i_z );

	rev_hes_sparsity.binary_union(arg[0], arg[0], i_z, rev_hes_sparsity);
	rev_hes_sparsity.binary_union(arg[1], arg[1], i_z, rev_hes_sparsity);

	if( jac_reverse[i_z] )
	{	rev_hes_sparsity.binary_union(
			arg[0], arg[0], arg[1], for_jac_sparsity); 
		rev_hes_sparsity.binary_union(
			arg[1], arg[1], arg[0], for_jac_sparsity); 
		rev_hes_sparsity.binary_union(
			arg[1], arg[1], arg[1], for_jac_sparsity); 
	}

	jac_reverse[arg[0]] |= jac_reverse[i_z];
	jac_reverse[arg[1]] |= jac_reverse[i_z];
	return;
}	

/*!
Reverse mode Hessian sparsity pattern for power function. 

The C++ source code corresponding to a unary operation has the form
\verbatim
	z = pow(x, y)
\endverbatim
where x and y are variables.

\copydetails reverse_sparse_hessian_binary_op
*/
inline void reverse_sparse_hessian_pow_op(
	size_t               i_z                ,
	const size_t*        arg                ,
	bool*                jac_reverse        ,
	vector_pack&         for_jac_sparsity   ,
	vector_pack&         rev_hes_sparsity   )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( arg[0] < i_z );
	CPPAD_ASSERT_UNKNOWN( arg[1] < i_z );

	rev_hes_sparsity.binary_union(arg[0], arg[0], i_z, rev_hes_sparsity);
	rev_hes_sparsity.binary_union(arg[1], arg[1], i_z, rev_hes_sparsity);

	if( jac_reverse[i_z] )
	{
		rev_hes_sparsity.binary_union(
			arg[0], arg[0], arg[0], for_jac_sparsity); 
		rev_hes_sparsity.binary_union(
			arg[0], arg[0], arg[1], for_jac_sparsity); 

		rev_hes_sparsity.binary_union(
			arg[1], arg[1], arg[0], for_jac_sparsity); 
		rev_hes_sparsity.binary_union(
			arg[1], arg[1], arg[1], for_jac_sparsity); 
	}

	// I cannot think of a case where this is necessary, but it including
	// it makes it like the other cases.
	jac_reverse[arg[0]] |= jac_reverse[i_z];
	jac_reverse[arg[1]] |= jac_reverse[i_z];
	return;
}	

CPPAD_END_NAMESPACE
# endif
