#ifndef UTILS_HPP
#define UTILS_HPP

#define CVIM_VERSION "0.0.1"

#define CTRL_KEY(k) ((k) & 0x1f)

void ensure(const bool condition, const char *msg);

#endif // UTILS_HPP