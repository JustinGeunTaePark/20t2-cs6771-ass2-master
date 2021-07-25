cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_test_constructor
   FILENAME "euclidean_vector_test_constructor.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_test_friend
   FILENAME "euclidean_vector_test_friend.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_test_utility_function
   FILENAME "euclidean_vector_test_utility_function.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_test_member_function
   FILENAME "euclidean_vector_test_member_function.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_test_operation
   FILENAME "euclidean_vector_test_operation.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)