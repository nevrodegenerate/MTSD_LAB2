#include "MDtoHTML.h"

int markdownToHtml(ifstream& file, string* outputText, int format) {
    string textBuffer;
    bool preform = false;
    bool paragr = false;
    int pos1 = 0;
    int pos2 = 0;
    int lastparagr = 0;

    const int arraySize = 5;
    //���������� ����� dataArray, � ����� ����� ������� ������� ��:
    //[0] - ���������� ������� ������� markdown
    //[1] - ������� ������� ������� markdown
    //[2] - ���������� ������� ������� html
    //[3] - ������� ������� ������� html
    //(� md �������� �� ����� �������� � ����������,
    //��� ���� ��������� ��������� �������� ��� ������������� ������ �������)
    string dataArray[arraySize][6] = {
        {"```", "```", "<pre>", "</pre>", "\x1b[7m", "\x1b[27m"}, //������ ������ ������ � �����������
        {"\n\n", "\n\n", "<p>", "</p>", "\n\n", "\n\n"}, //������ ������ ������ � ����������
        {"**", "**", "<b>", "</b>", "\x1b[1m", "\x1b[22m"},
        {"_", "_", "<i>", "</i>", "\x1b[3m", "\x1b[23m"},
        {"`", "`", "<tt>", "</tt>", "\x1b[7m", "\x1b[27m"} };

    while (getline(file, textBuffer)) {
        //����������
        if (textBuffer == dataArray[0][0] && !preform) {
            textBuffer.replace(0, dataArray[0][0].length(), dataArray[0][2 + format]);
            preform = true;
        }

        if (textBuffer == dataArray[0][1] && preform) {
            textBuffer.replace(0, dataArray[0][1].length(), dataArray[0][3 + format]);
            preform = false;
        }
        //���������
        while ((lastparagr = outputText->find(dataArray[1][0], lastparagr)) != string::npos) {
            paragr = true;
            outputText->replace(lastparagr, 2, dataArray[1][3 + format] + "\n" + dataArray[1][2 + format]);
        }

        if (!preform) {
            pos1 = 0;
            pos2 = 0;

            for (int i = 2; i < arraySize; i++) {
                while ((pos1 = textBuffer.find(dataArray[i][0], pos2)) != string::npos) {
                    if (textBuffer[pos1 + dataArray[i][0].length()] == ' '
                        || pos1 > 0 && textBuffer[pos1 - 1] != ' ') { //������� ������� �� � �������� �� ������ ��� �������� �����
                        break;
                    }
                    if ((pos2 = textBuffer.find(dataArray[i][1], pos1 + dataArray[i][2 + format].length()))
                        != string::npos
                        && textBuffer[pos2 + dataArray[i][1].length()] == ' '
                        || pos2 + dataArray[i][1].length() == textBuffer.length()
                        && pos2 > 0 && textBuffer[pos2 - 1] != ' ') {
                        textBuffer.replace(pos1, dataArray[i][0].length(), dataArray[i][2 + format]);
                        pos2 = textBuffer.find(dataArray[i][1], pos1 + dataArray[i][2 + format].length());
                        textBuffer.replace(pos2, dataArray[i][1].length(), dataArray[i][3 + format]);

                        //������ ������ ������ � ������ � ����� �������� �������� �������
                        string textSubStr = textBuffer.substr(pos1 + dataArray[i][2].length(),
                            pos2 - pos1 - dataArray[i][2].length());
                        int tmppos1 = 0;
                        int tmppos2 = 0;
                        for (int j = 2; j < arraySize; j++) {
                            if ((tmppos1 = textSubStr.find(dataArray[j][0])) != string::npos) {
                                if (textSubStr[tmppos1 + dataArray[j][0].length()] != ' ') {
                                    if (tmppos1 == 0 || textSubStr[tmppos1 - 1] == ' ') {
                                        return ERROR2;
                                    }
                                }
                                if ((tmppos2 = textSubStr.find(dataArray[j][1], tmppos1 + dataArray[j][0].length())
                                    != string::npos)) {
                                    if (tmppos2 == textSubStr.length() || textSubStr[tmppos2 + 1] != ' ') {
                                        if (tmppos2 > 0 && textSubStr[tmppos2 - 1] != ' ') {
                                            return ERROR2;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                        return ERROR1;
                }
            }
        }
        *outputText += textBuffer + "\n";
    }

    if (preform)
        return ERROR1;

    if (paragr) {
        *outputText = dataArray[1][2 + format] + *outputText;
        outputText->replace(outputText->length() - 1, 1, dataArray[1][3 + format]);
    }

    return SUCCESS;
}