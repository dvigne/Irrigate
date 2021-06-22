#include <QTE.hpp>

String TemplateEngine::renderTemplate(const String file, const String valueMap[][2], size_t count) {
  String workingCopy = file;
  int start;
  while((start = workingCopy.indexOf("{{")) !=  -1) {
    if (int end = workingCopy.indexOf("}}") + 2) {
      String braceIdent = workingCopy.substring(start, end);
      for (size_t i = 0; i < count; i++) {
        if (braceIdent.indexOf(valueMap[i][0]) != -1) {
          String replacement = valueMap[i][1];
          workingCopy.replace(braceIdent, replacement);
        }
      }
    }
    else {
      return "Template Error, missing closing braces. Please check syntax";
    }
  }
  return workingCopy;
}
