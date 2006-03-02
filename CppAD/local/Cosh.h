# ifndef CppADCoshIncluded
# define CppADCoshIncluded

/* -----------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-06 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */

/*
-------------------------------------------------------------------------------
$begin cosh$$
$spell
	Cpp
	namespace
	const
	cosh
$$

$index cosh$$
$index hyperbolic, cosine$$

$section The Hyperbolic Cosine Function$$

$table
$bold Syntax$$ 
$cnext 
$syntax%AD<%Base%> cosh (const AD<%Base%> &%x%)%$$
$tend

$fend 20$$

$head Description$$
Returns an
$syntax%AD<%Base%>%$$ object that is equal to
$syntax%
	cosh(%x%)
%$$
where $code cosh$$ has the same interpretation as
for the corresponding $xref/glossary/Base Type/base type/$$.


$head Base Type Requirement$$
A definition for the $code cosh$$ function
is automatically included (in the $code CppAD$$ namespace)
for the following 
$xref/glossary/Base Type/base types/$$:
$code float$$, $code double$$, $code complex<float>$$, 
and $code complex<double>$$.
If the $code cosh$$ function is used with any other base type, 
it must be a defined for that base type.

$head Derivative Assumption$$
It is assumed that
$latex \[
\begin{array}{lcr}
	\D{[ \cosh (x) ]}{x} & = & \sinh (x)  \\
	\D{[ \sin (x) ]}{x}  & = & \cosh (x)
\end{array}
\] $$



$head Example$$
$children%
	Example/Cosh.cpp
%$$
The file
$xref/Cosh.cpp/$$
contains an example and test of this function.   
It returns true if it succeeds and false otherwise.

$end
-------------------------------------------------------------------------------
*/

namespace CppAD {

	// define for float, double, std::complex<float>, std::complex<double>
	CppADStandardMathUnaryBaseAll(cosh)

	// define for AD types
	CppADStandardMathUnaryTemplate(cosh, CoshOp)
}

# endif 
