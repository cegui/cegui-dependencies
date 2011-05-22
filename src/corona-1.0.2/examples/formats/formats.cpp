#include <iostream>
#include <corona.h>
using namespace std;
using namespace corona;


void printFormats(FileFormatDesc** formats) {
  for (size_t i = 0; formats[i]; ++i) {
    cout << "  " << formats[i]->getDescription() << ":";
    for (size_t j = 0; j < formats[i]->getExtensionCount(); ++j) {
      cout << " " << formats[i]->getExtension(j);
    }
    cout << endl;
  }
}


int main() {
  cout << "Supported Read Formats:" << endl;
  printFormats(GetSupportedReadFormats());
  cout << endl;
  cout << "Supported Write Formats:" << endl;
  printFormats(GetSupportedWriteFormats());
}
