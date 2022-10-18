#include <stdio.h>
#include <omp.h>
#include <ompt.h>

ompt_start_tool_result_t *ompt_start_tool(unsigned int omp_version, char **runtime)
{
  printf("%s\n", runtime);
  return 0;
}
