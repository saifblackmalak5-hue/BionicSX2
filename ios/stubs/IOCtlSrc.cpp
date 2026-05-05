// BionicSX2 iOS stub for IOCtlSrc
#include "CDVD/CDVDdiscReader.h"
#include "CDVD/CDVD.h"
#include "common/Console.h"
#include "common/Error.h"

#include <cerrno>
#include <cstring>

IOCtlSrc::IOCtlSrc(std::string filename)
	: m_filename(std::move(filename)), m_device(-1), m_sectors(0), m_layer_break(0), m_media_type(-1)
{
}

IOCtlSrc::~IOCtlSrc()
{
}

bool IOCtlSrc::Reopen(Error* error)
{
	return false;
}

void IOCtlSrc::SetSpindleSpeed(bool restore_defaults) const
{
}

u32 IOCtlSrc::GetSectorCount() const
{
	return 0;
}

u32 IOCtlSrc::GetLayerBreakAddress() const
{
	return 0;
}

s32 IOCtlSrc::GetMediaType() const
{
	return -1;
}

const std::vector<toc_entry>& IOCtlSrc::ReadTOC() const
{
	static std::vector<toc_entry> empty_toc;
	return empty_toc;
}

bool IOCtlSrc::ReadSectors2048(u32 sector, u32 count, u8* buffer) const
{
	return false;
}

bool IOCtlSrc::ReadSectors2352(u32 sector, u32 count, u8* buffer) const
{
	return false;
}

bool IOCtlSrc::ReadDVDInfo()
{
	return false;
}

bool IOCtlSrc::ReadCDInfo()
{
	return false;
}

bool IOCtlSrc::ReadTrackSubQ(cdvdSubQ* subQ) const
{
	return false;
}

bool IOCtlSrc::DiscReady()
{
	return false;
}
