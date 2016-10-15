//
//  Function1D.hpp
//  XLPricer
//  Base class for a functor, which can be overloaded manually or be initialised with a std::function.
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef Function1D_hpp
#define Function1D_hpp

#include <functional>

using std::function;

class Function1D
{
public:
    virtual double operator() (double x) const = 0;
};


#endif /* Function1D_hpp */
