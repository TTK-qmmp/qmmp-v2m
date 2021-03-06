#include "v2mhelper.h"
#include <libv2m/v2mconv.h>
#include <libv2m/sounddef.h>
#include <math.h>

static bool v2m_initialized = false;
int load_and_convert(unsigned char *module, qint64 size, uint8_t **conv, int *convlen)
{
    if(!v2m_initialized)
    {
        sdInit();
        v2m_initialized = true;
    }

    ssbase base;
    const int ver = CheckV2MVersion(module, size, base);
    if(ver < 0)
    {
        return -1;
    }

    ConvertV2M(module, size, conv, convlen);
    return 0;
}


V2MHelper::V2MHelper(const QString &path)
    : m_path(path)
{
    m_info = (decode_info*)calloc(sizeof(decode_info), 1);
}

V2MHelper::~V2MHelper()
{
    deinit();
}

void V2MHelper::deinit()
{
    if(m_info) 
    {
        if(m_info->tune)
        {
            free(m_info->tune);
        }

        if(m_info->input)
        {
            m_info->input->Close();
            delete m_info->input;
        }
        free(m_info);
    }
}

bool V2MHelper::initialize()
{
    QFile file(m_path);
    if(!file.open(QFile::ReadOnly))
    {
        qWarning("V2MHelper: open file failed");
        return false;
    }

    const qint64 size = file.size();
    const QByteArray module = file.readAll();

    int convlen;
    if(load_and_convert((unsigned char *)module.constData(), size, &m_info->tune, &convlen) < 0)
    {
        qWarning("V2MHelper: load_and_convert error");
        return false;
    }

    m_info->input = new V2MPlayer;
    m_info->input->Init();
    m_info->input->Open(m_info->tune);

    m_info->bitrate = size * 8.0 / totalTime() + 1.0f;
    m_info->input->Play();

    return true;
}

qint64 V2MHelper::totalTime() const
{
    return m_info->input->Length() * 1000;
}

void V2MHelper::seek(qint64 time)
{
    m_info->input->Play(time);
}

int V2MHelper::bitrate() const
{
    return m_info->bitrate;
}

int V2MHelper::sampleRate() const
{
    return 44100;
}

int V2MHelper::channels() const
{
    return 2;
}

int V2MHelper::bitsPerSample() const
{
    return 32;
}

qint64 V2MHelper::read(unsigned char *data, qint64 maxSize)
{
    if(!m_info->input->IsPlaying())
    {
        return 0;
    }

    const int sampleSize = (bitsPerSample() >> 3) * channels();
    const int samples = maxSize / sampleSize;

    m_info->input->Render((float*)data, samples);

    return maxSize;
}
