#include <cstdint>
#include <iterator>
#include <vector>

namespace mystd
{

using It = std::vector<std::int32_t>::iterator;
using DifferenceType = It::difference_type;

void advance(It &it, DifferenceType n);

DifferenceType distance(It first, It last);

It next(It it, DifferenceType n = 1);

It prev(It it, DifferenceType n = -1);

} // namespace mystd
