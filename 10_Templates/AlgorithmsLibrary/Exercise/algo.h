#pragma once

namespace mystd
{

template <typename InputIter1, typename InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
{
}

template <typename OutputIter, typename Size, typename T>
OutputIter fill_n(OutputIter first, Size count, const T &value)
{
}

template <typename ForwardIter, typename T>
void iota(ForwardIter first, ForwardIter last, T value)
{
}

template <typename InptIter, typename OutputIter>
OutputIter copy(InptIter first, InptIter last, OutputIter d_first)
{
}

template <typename InputIter, typename T>
T accumulate(InputIter first, InputIter last, T init)
{
}

} // namespace mystd
