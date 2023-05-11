//
// Created by Q on 2023/5/10.
//

#ifndef STL_LEARNING_MY_CONFIG_H
#define STL_LEARNING_MY_CONFIG_H
#define  __STL_USE_EXCEPTIONS
# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_THROW(x) throw x
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }
#   define __STL_NULL_TMPL_ARGS <>
# else
#   define __STL_TRY
#   define __STL_CATCH_ALL if (false)
#   define __STL_THROW(x)
#   define __STL_RETHROW
#   define __STL_NOTHROW
#   define __STL_UNWIND(action)
#   define __STL_NULL_TMPL_ARGS
# endif

#endif //STL_LEARNING_MY_CONFIG_H
