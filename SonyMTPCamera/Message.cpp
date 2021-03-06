#include "pch.h"
#include "Message.h"

Message::Message(WORD command)
    : m_command(command),
      m_dataLen(0),
      m_data(nullptr)
{

}

Message::Message(const Message& rhs)
    : m_command(rhs.m_command),
      m_dataLen(rhs.m_dataLen)
{
    if (m_dataLen > 0) {
        m_data = new BYTE[m_dataLen];

        memcpy(m_data, rhs.m_data, m_dataLen);
    }
}

Message::~Message()
{
    SetData(nullptr, 0);
}

void
Message::Allocate(DWORD dataLen)
{
    SetData(nullptr, 0);

    if (dataLen)
    {
        m_data = new BYTE[dataLen];
        memset(m_data, 0, dataLen);
        m_dataLen = dataLen;
    }
}

void
Message::SetCommand(WORD command)
{
    m_command = command;
}

WORD
Message::GetCommand()
{
    return m_command;
}

BYTE*
Message::GetData()
{
    return m_data;
}

DWORD
Message::GetDataLen()
{
    return m_dataLen;
}

bool
Message::AddData(BYTE* data, DWORD dataLen)
{
    // This will ignore any data bigger than allocated size
    DWORD bytesToWrite = min(m_dataLen - m_writeOffset, dataLen);

    if (m_data && bytesToWrite > 0)
    {
        memcpy(m_data + m_writeOffset, data, bytesToWrite);
        m_writeOffset += bytesToWrite;
    }

    return true;
}

bool
Message::SetData(BYTE* data, DWORD dataLen)
{
    if (m_data)
    {
        delete[] m_data;
        m_data = nullptr;
        m_dataLen = 0;
    }

    if (dataLen > 0 && data) {
        m_data = new BYTE[dataLen];
        memcpy(m_data, data, dataLen);
        m_dataLen = dataLen;
    }

    return true;
}

bool
Message::AddParam(DWORD param)
{
    m_params.push_back(param);

    return true;
}

std::list<DWORD>
Message::GetParams()
{
    return m_params;
}

std::wstring
Message::Dump()
{
    std::wostringstream result;

    result << "command: ";

    result << std::hex << std::setw(4) << std::setfill(L'0') << m_command;
    result << "\ndataLen: ";
    result << m_dataLen;
    result << "\ndata: [ ";

    DWORD i, j, k;

    for (i = 0; i < m_dataLen; i += 16)
    {
        result << "\n" << std::hex << std::setw(4) << std::setfill(L'0') << i << ": ";

        std::wostringstream chars;

        for (j = 0; j < 16 && i+ j < m_dataLen; j++)
        {
            BYTE d = m_data[i + j];

            result << std::hex << std::setw(2) << std::setfill(L'0') << (WORD)d << " ";

            if (d >= 32 && d <= 127)
            {
                chars << (char)d;
            }
            else
            {
                chars << '.';
            }
        }

        for (k = j; k < 16; k++)
        {
            result << "   ";
        }

        result << chars.str();
    }

    result << "\n]";

    return result.str();
}

bool
Message::IsSuccess()
{
    return m_command == COMMAND_RESULT_SUCCESS;
}