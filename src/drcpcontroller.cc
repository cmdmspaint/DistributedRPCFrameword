#include "drpccontroller.h"

DrpcController::DrpcController()
{
    m_failed = false;
    m_errText = "";
}

void DrpcController::Reset()
{
    m_failed = false;
    m_errText = "";
}

bool DrpcController::Failed() const
{
    return m_failed;
}

std::string DrpcController::ErrorText() const
{
    return m_errText;
}

void DrpcController::SetFailed(const std::string& reason)
{
    m_failed = true;
    m_errText = reason;
}

void DrpcController::StartCancel()
{

}
bool DrpcController::IsCanceled()
{

}
void DrpcController::NotifyOnCancel(google::protobuf::Closure* callback)
{

}