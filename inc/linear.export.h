#ifndef LINEAR_EXPORT_H
#define LINEAR_EXPORT_H


#ifdef WIN
#ifdef  LINEAR_EXPORTS
#define LINEAR_EXPORT __declspec(dllexport)
#else
#define LINEAR_EXPORT __declspec(dllimport)
#endif
#else
#define LINEAR_EXPORT __attribute__((visibility("default")))
#endif
#endif