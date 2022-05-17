#include "decoderv2mfactory.h"
#include "v2mhelper.h"
#include "decoder_v2m.h"

#include <QMessageBox>

bool DecoderV2MFactory::canDecode(QIODevice *input) const
{
    QFile *file = static_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    V2MHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderV2MFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("V2M Plugin");
    properties.shortName = "v2m";
    properties.filters << "*.v2m";
    properties.description = "V2 Module Player File";
    properties.protocols << "file";
    properties.noInput = true;
    properties.hasAbout = true;
    return properties;
}

Decoder *DecoderV2MFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderV2M(path);
}

QList<TrackInfo*> DecoderV2MFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    V2MHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "V2 Module");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderV2MFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

void DecoderV2MFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderV2MFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About V2M Reader Plugin"),
                       tr("Qmmp V2M Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderV2MFactory::translation() const
{
    return QString();
}
