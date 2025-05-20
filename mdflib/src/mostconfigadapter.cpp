/*
* Copyright 2025 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "mdf/mostconfigadapter.h"
#include "mdf/ichannel.h"
#include "mdf/ichannelgroup.h"
#include "mdf/idatagroup.h"
#include "mdf/mdflogstream.h"


namespace mdf {
MostConfigAdapter::MostConfigAdapter(const MdfWriter& writer)
    : IConfigAdapter(writer) {
  BusType(MdfBusType::MOST);
  BusName("MOST");
}

void MostConfigAdapter::CreateConfig(IDataGroup& dg_block) {
  // Transfer internal properties to the data and channel groups.
  dg_block.MandatoryMembersOnly(MandatoryMembersOnly());
  if (StorageType() == MdfStorageType::MlsdStorage) {
    StorageType(MdfStorageType::VlsdStorage);
    MDF_INFO() << "Storage type MLSD is not supported for MOST buses. "
               << "Changing to VLSD storage.";
  }

  CreateMostMessage(dg_block);
  CreateMostPacket(dg_block);
  CreateMostEthernetPacket(dg_block);
  CreateMostSignalState(dg_block);
  CreateMostMaxPosInfo(dg_block);
  CreateMostBoundDesc(dg_block);
  CreateMostAllocTable(dg_block);
  CreateMostSysLockState(dg_block);
  CreateMostShutdownFlag(dg_block);
}

void MostConfigAdapter::CreateMostMessage(IDataGroup& data_group) const {
  const IChannel* cn_data_byte = nullptr;
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("Message"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateMessageChannel(*cg_message);
    cn_data_byte = cg_message->GetChannel("MOST_Message.DataBytes");
    CreateSourceInformation(*cg_message);
  }
  if (StorageType() == MdfStorageType::VlsdStorage && cn_data_byte != nullptr) {
    // Need to add a special CG group for the data samples.
    // Also need to set the VLSD Record ID. The CreateChannelGroup function
    // creates a valid record ID.
    // The VLSD CG group doesn't have any channels.

    if (auto* cg_samples_frame = data_group.CreateChannelGroup("");
        cg_samples_frame != nullptr) {
      cg_samples_frame->Flags(CgFlag::VlsdChannel);
      cn_data_byte->VlsdRecordId(cg_samples_frame->RecordId());
    }
  }
}

void MostConfigAdapter::CreateMostPacket(IDataGroup& data_group) const {
  const IChannel* cn_data_byte = nullptr;
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("Packet"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreatePacketChannel(*cg_message);
    cn_data_byte = cg_message->GetChannel("MOST_Packet.DataBytes");
    CreateSourceInformation(*cg_message);
  }
  if (StorageType() == MdfStorageType::VlsdStorage && cn_data_byte != nullptr) {
    // Need to add a special CG group for the data samples.
    // Also need to set the VLSD Record ID. The CreateChannelGroup function
    // creates a valid record ID.
    // The VLSD CG group doesn't have any channels.

    if (auto* cg_samples_frame = data_group.CreateChannelGroup("");
        cg_samples_frame != nullptr) {
      cg_samples_frame->Flags(CgFlag::VlsdChannel);
      cn_data_byte->VlsdRecordId(cg_samples_frame->RecordId());
    }
  }
}


void MostConfigAdapter::CreateMostEthernetPacket(IDataGroup& data_group) const {
  const IChannel* cn_data_byte = nullptr;
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("EthernetPacket"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateEthernetPacketChannel(*cg_message);
    cn_data_byte = cg_message->GetChannel("MOST_EthernetPacket.DataBytes");
    CreateSourceInformation(*cg_message);
  }
  if (StorageType() == MdfStorageType::VlsdStorage && cn_data_byte != nullptr) {
    // Need to add a special CG group for the data samples.
    // Also need to set the VLSD Record ID. The CreateChannelGroup function
    // creates a valid record ID.
    // The VLSD CG group doesn't have any channels.

    if (auto* cg_samples_frame = data_group.CreateChannelGroup("");
        cg_samples_frame != nullptr) {
      cg_samples_frame->Flags(CgFlag::VlsdChannel);
      cn_data_byte->VlsdRecordId(cg_samples_frame->RecordId());
    }
  }
}

void MostConfigAdapter::CreateMostSignalState(IDataGroup& data_group) const {
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("SignalState"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateSignalStateChannel(*cg_message);
    CreateSourceInformation(*cg_message);
  }
}

void MostConfigAdapter::CreateMostMaxPosInfo(IDataGroup& data_group) const {
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("MaxPosInfo"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateMaxPosInfoChannel(*cg_message);
    CreateSourceInformation(*cg_message);
  }
}

void MostConfigAdapter::CreateMostBoundDesc(IDataGroup& data_group) const {
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("BoundDesc"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateBoundDescChannel(*cg_message);
    CreateSourceInformation(*cg_message);
  }
}

void MostConfigAdapter::CreateMostAllocTable(IDataGroup& data_group) const {
  const IChannel* cn_data_byte = nullptr;
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("AllocTable"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateAllocTableChannel(*cg_message);
    cn_data_byte = cg_message->GetChannel("MOST_AllocTable.TableData");
    CreateSourceInformation(*cg_message);
  }
  if (StorageType() == MdfStorageType::VlsdStorage && cn_data_byte != nullptr) {
    // Need to add a special CG group for the data samples.
    // Also need to set the VLSD Record ID. The CreateChannelGroup function
    // creates a valid record ID.
    // The VLSD CG group doesn't have any channels.

    if (auto* cg_samples_frame = data_group.CreateChannelGroup("");
        cg_samples_frame != nullptr) {
      cg_samples_frame->Flags(CgFlag::VlsdChannel);
      cn_data_byte->VlsdRecordId(cg_samples_frame->RecordId());
    }
  }
}


void MostConfigAdapter::CreateMostSysLockState(IDataGroup& data_group) const {
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("SysLockState"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateSysLockStateChannel(*cg_message);
    CreateSourceInformation(*cg_message);
  }
}

void MostConfigAdapter::CreateMostShutdownFlag(IDataGroup& data_group) const {
  if (IChannelGroup* cg_message = data_group.CreateChannelGroup(
          MakeGroupName("ShutdownFlag"));
      cg_message != nullptr) {
    cg_message->PathSeparator('.');
    cg_message->Flags(CgFlag::PlainBusEvent | CgFlag::BusEvent);
    CreateTimeChannel(*cg_message,"t");
    CreateShutdownFlagChannel(*cg_message);
    CreateSourceInformation(*cg_message);
  }
}

void MostConfigAdapter::CreateEthernetPacketChannel(IChannelGroup& channel_group) const {
  const bool mandatory_members_only = MandatoryMembersOnly();
  IChannel* parent_frame = channel_group.CreateChannel("MOST_EthernetPacket");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_EthernetPacket channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  if (mandatory_members_only) {
    parent_frame->DataBytes(36-8);
  } else {
    parent_frame->DataBytes(42-8);
  }
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateSpeedChannel(*parent_frame, 9);
  CreateTransferTypeChannel(*parent_frame, 9);
  CreateDirectionChannel(*parent_frame, 9);
  CreateSourceChannel(*parent_frame, 10, 48);
  CreateDestinationChannel(*parent_frame,16, 48);
  CreateSpecifiedBytesChannel(*parent_frame, 22);
  CreateReceivedBytesChannel(*parent_frame, 24);
  CreateDataLengthChannel(*parent_frame, 26);
  if (mandatory_members_only) {
    CreateDataBytesChannel(*parent_frame, 28);
    return;
  }
  CreateCrcChannel(*parent_frame, 28, 32);
  CreateCompleteAckChannel(*parent_frame, 32);
  CreatePreemptiveAckChannel(*parent_frame, 32);
  CreateTxAckChannel(*parent_frame, 33);
  CreateDataBytesChannel(*parent_frame, 34);
}

void MostConfigAdapter::CreatePacketChannel(IChannelGroup& channel_group) const {
  const bool mandatory_members_only = MandatoryMembersOnly();
  auto* parent_frame = channel_group.CreateChannel("MOST_Packet");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_Packet channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  if (mandatory_members_only) {
    parent_frame->DataBytes(28-8);
  } else {
    parent_frame->DataBytes(35-8);
  }
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateMandatoryMembers(*parent_frame); // 28 bytes
  if (mandatory_members_only) {
    CreateDataBytesChannel(*parent_frame, 20);
    return;
  }
  CreateCrcChannel(*parent_frame, 20, 32);
  CreateCompleteAckChannel(*parent_frame, 24);
  CreatePreemptiveAckChannel(*parent_frame, 24);
  CreateTxAckChannel(*parent_frame, 25);
  CreatePacketIndexChannel(*parent_frame, 26);
  CreateDataBytesChannel(*parent_frame, 27);
}

void MostConfigAdapter::CreateMessageChannel(IChannelGroup& channel_group) const {
  const bool mandatory_members_only = MandatoryMembersOnly();
  auto* parent_frame = channel_group.CreateChannel("MOST_Message");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_Message channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  if (mandatory_members_only) {
    parent_frame->DataBytes(28-8);
  } else {
    parent_frame->DataBytes(35-8);
  }
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateMandatoryMembers(*parent_frame); // 28 bytes
  if (mandatory_members_only) {
    CreateDataBytesChannel(*parent_frame, 20);
    return;
  }

  CreateTxFailedChannel(*parent_frame, 24);
  CreateCrcChannel(*parent_frame, 20, 32);
  CreateCompleteAckChannel(*parent_frame, 24);
  CreatePreemptiveAckChannel(*parent_frame, 24);
  CreateTxAckChannel(*parent_frame, 25);
  CreatePacketIndexChannel(*parent_frame, 26);
  CreatePacketTypeChannel(*parent_frame, 25);
  CreateDataBytesChannel(*parent_frame, 27);
}

void MostConfigAdapter::CreateSignalStateChannel(IChannelGroup& channel_group) const {
  auto* parent_frame = channel_group.CreateChannel("MOST_SignalState");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_SignalState channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  parent_frame->DataBytes(10-8);
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateStateChannel(*parent_frame, 9);
}

void MostConfigAdapter::CreateMaxPosInfoChannel(IChannelGroup& channel_group) const {
  auto* parent_frame = channel_group.CreateChannel("MOST_MaxPosInfo");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_MaxPosInfo channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  parent_frame->DataBytes(10-8);
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateDeviceCountChannel(*parent_frame, 9);
}

void MostConfigAdapter::CreateBoundDescChannel(IChannelGroup& channel_group) const {
  auto* parent_frame = channel_group.CreateChannel("MOST_BoundDesc");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_BoundDesc channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  parent_frame->DataBytes(11-8);
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateSbcChannel(*parent_frame, 9);
}

void MostConfigAdapter::CreateAllocTableChannel(IChannelGroup& channel_group) const {
  auto* parent_frame = channel_group.CreateChannel("MOST_AllocTable");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_AllocTable channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  parent_frame->DataBytes(22-8);
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateFreeBytesChannel(*parent_frame, 9);
  CreateTableLayoutChannel(*parent_frame, 11);
  CreateTableLengthChannel(*parent_frame, 12);
  CreateTableDataChannel(*parent_frame, 14);
}

void MostConfigAdapter::CreateSysLockStateChannel(IChannelGroup& channel_group) const {
  auto* parent_frame = channel_group.CreateChannel("MOST_SysLockState");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_SysLockState channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  parent_frame->DataBytes(10-8);
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateLockStateChannel(*parent_frame, 9);
}

void MostConfigAdapter::CreateShutdownFlagChannel(IChannelGroup& channel_group) const {
  auto* parent_frame = channel_group.CreateChannel("MOST_ShutdownFlag");
  if (parent_frame == nullptr) {
    MDF_ERROR() << "Failed to create the MOST_ShutdownFlag channel.";
    return;
  }

  parent_frame->Type(ChannelType::FixedLength);
  parent_frame->Sync(ChannelSyncType::None);
  parent_frame->DataBytes(10-8);
  parent_frame->Flags(CnFlag::BusEvent);
  parent_frame->DataType(ChannelDataType::ByteArray);
  if (!network_name_.empty()) {
    CreateSourceInformation(*parent_frame);
  }
  CreateBusChannel(*parent_frame);
  CreateShutdownChannel(*parent_frame, 9);
}

void MostConfigAdapter::CreateMandatoryMembers(IChannel& parent_frame) const {
  CreateBusChannel(parent_frame);
  CreateSpeedChannel(parent_frame, 9);
  CreateTransferTypeChannel(parent_frame, 9);
  CreateDirectionChannel(parent_frame, 9);
  CreateSourceChannel(parent_frame, 10, 16);
  CreateDestinationChannel(parent_frame,12, 16);
  CreateSpecifiedBytesChannel(parent_frame, 14);
  CreateReceivedBytesChannel(parent_frame, 16);
  CreateDataLengthChannel(parent_frame, 18);

}

void MostConfigAdapter::CreateSpeedChannel(IChannel& parent_channel,
                                           uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".Speed";

  if (IChannel* speed = CreateBitsChannel(parent_channel, name.str(),
                                          byte_offset, 0, 2);
      speed != nullptr) {
    speed->Flags(CnFlag::BusEvent | CnFlag::RangeValid);
    speed->Range(0,2);

    if (IChannelConversion* cc_speed = speed->CreateChannelConversion();
        cc_speed != nullptr) {
      cc_speed->Type(ConversionType::ValueToText);
      cc_speed->Name("SpeedEnum");
      cc_speed->Parameter(0, 0.0);
      cc_speed->Parameter(1, 1.0);
      cc_speed->Parameter(2, 2.0);
      cc_speed->Reference(0, "MOST25");
      cc_speed->Reference(1, "MOST50");
      cc_speed->Reference(2, "MOST150");
      cc_speed->Reference(3, ""); // Default text

      CcComment cc_comment("MOST Speed Enumerate");
      cc_speed->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateStateChannel(IChannel& parent_channel,
                                           uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".State";

  if (IChannel* state = CreateBitsChannel(parent_channel, name.str(),
                                          byte_offset, 0, 8);
      state != nullptr) {
    state->Flags(CnFlag::BusEvent | CnFlag::RangeValid);
    state->Range(0,32);

    if (IChannelConversion* cc_state = state->CreateChannelConversion();
        cc_state != nullptr) {
      cc_state->Type(ConversionType::ValueToText);
      cc_state->Name("SignalStateEnum");
      cc_state->Parameter(0, 0.0);
      cc_state->Parameter(1, 1.0);
      cc_state->Parameter(2, 2.0);
      cc_state->Parameter(3, 3.0);
      cc_state->Parameter(4, 16.0);
      cc_state->Parameter(5, 32.0);
      cc_state->Reference(0, "Unknown");
      cc_state->Reference(1, "On Lock");
      cc_state->Reference(2, "Off");
      cc_state->Reference(3, "On No Lock");
      cc_state->Reference(4, "Stable Lock");
      cc_state->Reference(5, "Critical Unlock");
      cc_state->Reference(6, ""); // Default text

      CcComment cc_comment("MOST Signal State Enumerate");
      cc_state->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateSbcChannel(IChannel& parent_channel,
                                           uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".SBC";

  if (IChannel* sbc = CreateBitsChannel(parent_channel, name.str(),
                                          byte_offset, 0, 16);
      sbc != nullptr) {
    sbc->Flags(CnFlag::BusEvent);
    sbc->Unit("B");

    CnComment cn_comment("Synchronous Bandwidth Control. Width for synchronous area");
    sbc->SetCnComment(cn_comment);
  }
}

void MostConfigAdapter::CreateDeviceCountChannel(IChannel& parent_channel,
                                         uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".DeviceCount";

  if (IChannel* count =
          CreateBitsChannel(parent_channel, name.str(), byte_offset, 0, 8);
      count != nullptr) {
    count->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreateFreeBytesChannel(IChannel& parent_channel,
                                                 uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".FreeByteCount";

  if (IChannel* count =
          CreateBitsChannel(parent_channel, name.str(), byte_offset, 0, 16);
      count != nullptr) {
    count->Flags(CnFlag::BusEvent);

    CnUnit unit_comment("B");
    count->SetCnUnit(unit_comment);

    CnComment cn_comment("Number of free bytes on the synchronous channel.");
    count->SetCnComment(cn_comment);
  }
}

void MostConfigAdapter::CreateTableLayoutChannel(IChannel& parent_channel,
                                                  uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".TableLayout";

  if (IChannel* layout = CreateBitsChannel(parent_channel, name.str(),
                                        byte_offset,0, 8);
      layout != nullptr) {
    layout->Flags(CnFlag::BusEvent);

    if (auto* cc_layout = layout->CreateChannelConversion();
        cc_layout != nullptr) {
      cc_layout->Type(ConversionType::ValueToText);
      cc_layout->Name("TableLayoutEnum");
      cc_layout->Parameter(0, 0.0);
      cc_layout->Parameter(1, 1.0);
      cc_layout->Reference(0, "Channel Resource Allocation Table");
      cc_layout->Reference(1, "Label List");
      cc_layout->Reference(2, ""); // Default text

      CcComment cc_comment("Table Layout Enumerate");
      cc_layout->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateTableLengthChannel(IChannel& parent_channel,
                                                uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".TableLength";
  if (IChannel* length = CreateBitsChannel(parent_channel, name.str(),
      byte_offset,0, 16);
      length != nullptr ) {
    length->Flags(CnFlag::BusEvent);
    length->Unit("B");
  }
}

void MostConfigAdapter::CreateTableDataChannel(IChannel& parent_channel,
                                               uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".TableData";
  if (IChannel* bytes = CreateBitsChannel(parent_channel, name.str(),
                                          byte_offset,0, 64);
      bytes != nullptr ) {
    bytes->Flags(CnFlag::BusEvent);
    bytes->DataType(ChannelDataType::ByteArray);
    bytes->Type(ChannelType::VariableLength);
  }
}

void MostConfigAdapter::CreateLockStateChannel(IChannel& parent_channel,
                                                 uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".SysLockState";

  if (IChannel* state = CreateBitChannel(parent_channel, name.str(),
                                           byte_offset,0);
      state != nullptr) {
    state->Flags(CnFlag::BusEvent);

    if (IChannelConversion* cc_state = state->CreateChannelConversion();
        cc_state != nullptr) {
      cc_state->Type(ConversionType::ValueToText);
      cc_state->Name("RingStateEnum");
      cc_state->Parameter(0, 0.0);
      cc_state->Parameter(1, 1.0);
      cc_state->Reference(0, "Ring is Open");
      cc_state->Reference(1, "Ring is Closed");
      cc_state->Reference(2, ""); // Default text

      CcComment cc_comment("Ring Open/Closed Enumerate");
      cc_state->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateShutdownChannel(IChannel& parent_channel,
                                               uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".ShutdownFlag";

  if (IChannel* state = CreateBitChannel(parent_channel, name.str(),
                                         byte_offset,0);
      state != nullptr) {
    state->Flags(CnFlag::BusEvent);

    if (IChannelConversion* cc_state = state->CreateChannelConversion();
        cc_state != nullptr) {
      cc_state->Type(ConversionType::ValueToText);
      cc_state->Name("ShutdownEnum");
      cc_state->Parameter(0, 0.0);
      cc_state->Parameter(1, 1.0);
      cc_state->Reference(0, "No Shutdown");
      cc_state->Reference(1, "Shutdown");
      cc_state->Reference(2, ""); // Default text

      CcComment cc_comment("Shutdown Flag Enumerate");
      cc_state->SetCcComment(cc_comment);
    }
  }
}


void MostConfigAdapter::CreateTransferTypeChannel(IChannel& parent_channel,
                                                  uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".TransferType";

  if (IChannel* type = CreateBitChannel(parent_channel, name.str(),
                                        byte_offset,2);
      type != nullptr) {
      type->Flags(CnFlag::BusEvent);

    if (auto* cc_type = type->CreateChannelConversion();
        cc_type != nullptr) {
      cc_type->Type(ConversionType::ValueToText);
      cc_type->Name("TransferTypeEnum");
      cc_type->Parameter(0, 0.0);
      cc_type->Parameter(1, 1.0);
      cc_type->Reference(0, "Spy");
      cc_type->Reference(1, "Node");
      cc_type->Reference(2, ""); // Default text

      CcComment cc_comment("Transfer Type Enumerate");
      cc_type->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateDirectionChannel(IChannel& parent_channel,
                                               uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".Dir";

  if (IChannel* dir = CreateBitChannel(parent_channel, name.str(),
                                       byte_offset,3);
      dir != nullptr) {
    dir->Flags(CnFlag::BusEvent);

    if (auto* cc_dir = dir->CreateChannelConversion();
        cc_dir != nullptr) {
      cc_dir->Type(ConversionType::ValueToText);
      cc_dir->Name("DirEnum");
      cc_dir->Parameter(0, 0.0);
      cc_dir->Parameter(1, 1.0);
      cc_dir->Reference(0, "Rx");
      cc_dir->Reference(1, "Tx");
      cc_dir->Reference(2, ""); // Default text

      CcComment cc_comment("Transmit or Receive Enumerate");
      cc_dir->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateSourceChannel(IChannel& parent_channel,
                    uint32_t byte_offset, uint32_t nof_bits) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".Source";
  if (IChannel* source = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, nof_bits);
      source != nullptr ) {
    source->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreateDestinationChannel(IChannel& parent_channel,
                       uint32_t byte_offset, uint32_t nof_bits) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".Destination";
  if (IChannel* dest = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, nof_bits);
      dest != nullptr ) {
    dest->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreateSpecifiedBytesChannel(IChannel& parent_channel,
                             uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".SpecifiedDataByteCount";
  if (IChannel* count = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, 16);
      count != nullptr) {
    count->Flags(CnFlag::BusEvent);
    count->Unit("B");
  }
}

void MostConfigAdapter::CreateReceivedBytesChannel(IChannel& parent_channel,
                                                   uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".ReceivedDataByteCount";
  if (IChannel* count = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, 16);
      count != nullptr) {
    count->Flags(CnFlag::BusEvent);
    count->Unit("B");
  }
}

void MostConfigAdapter::CreateDataLengthChannel(IChannel& parent_channel,
                                                   uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".DataLength";
  if (IChannel* length = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, 16);
      length != nullptr) {
    length->Flags(CnFlag::BusEvent);
    length->Unit("B");
  }
}

void MostConfigAdapter::CreateDataBytesChannel(IChannel& parent_channel,
                                                uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".DataBytes";
  if (IChannel* bytes = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, 64);
      bytes != nullptr ) {
    bytes->Flags(CnFlag::BusEvent);
    bytes->DataType(ChannelDataType::ByteArray);
    bytes->Type(ChannelType::VariableLength);
  }
}

void MostConfigAdapter::CreateTxFailedChannel(IChannel& parent_channel,
                                                uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".TxFailed";
  if (IChannel* failed = CreateBitChannel(parent_channel, name.str(),
          byte_offset,6);
      failed != nullptr) {
    failed->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreateCrcChannel(IChannel& parent_channel,
                             uint32_t byte_offset, uint32_t nof_bits) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".CRC";
  if (IChannel* crc = CreateBitsChannel(parent_channel, name.str(),
        byte_offset,0, nof_bits);
      crc != nullptr ) {
    crc->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreateCompleteAckChannel(IChannel& parent_channel,
                                               uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".CAck";

  if (IChannel* c_ack = CreateBitsChannel(parent_channel, name.str(),
                                       byte_offset,0, 3);
      c_ack != nullptr) {
    c_ack->Flags(CnFlag::BusEvent | CnFlag::RangeValid);
    c_ack->Range(0,4);
    if (auto* cc_ack = c_ack->CreateChannelConversion();
        cc_ack != nullptr) {
      cc_ack->Type(ConversionType::ValueToText);
      cc_ack->Name("CompleteAckEnum");
      cc_ack->Parameter(0, 0.0);
      cc_ack->Parameter(1, 1.0);
      cc_ack->Parameter(2, 4.0);
      cc_ack->Reference(0, "No Response");
      cc_ack->Reference(1, "CRC Error");
      cc_ack->Reference(2, "OK");
      cc_ack->Reference(3, "Unknown"); // Default text

      CcComment cc_comment("Complete ACK Enumerate");
      cc_ack->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreatePreemptiveAckChannel(IChannel& parent_channel,
                                                 uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".PAck";

  if (IChannel* p_ack = CreateBitsChannel(parent_channel, name.str(),
                                          byte_offset,3, 3);
      p_ack != nullptr) {
    p_ack->Flags(CnFlag::BusEvent | CnFlag::RangeValid);
    p_ack->Range(0,4);
    if (auto* cc_ack = p_ack->CreateChannelConversion();
        cc_ack != nullptr) {
      cc_ack->Type(ConversionType::ValueToText);
      cc_ack->Name("PreemptiveAckEnum");
      cc_ack->Parameter(0, 0.0);
      cc_ack->Parameter(1, 1.0);
      cc_ack->Parameter(2, 4.0);
      cc_ack->Reference(0, "No Response");
      cc_ack->Reference(1, "Buffer Full");
      cc_ack->Reference(2, "OK");
      cc_ack->Reference(3, "Unknown"); // Default text

      CcComment cc_comment("Pre-emptive ACK Enumerate");
      cc_ack->SetCcComment(cc_comment);
    }
  }
}

void MostConfigAdapter::CreateTxAckChannel(IChannel& parent_channel,
                                           uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".AckNAck";
  if (IChannel* ack = CreateBitsChannel(parent_channel, name.str(),
                                          byte_offset,0, 4);
      ack != nullptr ) {
    ack->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreatePacketIndexChannel(IChannel& parent_channel,
                                           uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".PIndex";
  if (IChannel* index = CreateBitsChannel(parent_channel, name.str(),
                    byte_offset,0, 8);
      index != nullptr) {
    index->Flags(CnFlag::BusEvent);
  }
}

void MostConfigAdapter::CreatePacketTypeChannel(IChannel& parent_channel,
                                                 uint32_t byte_offset) const {
  std::ostringstream name;
  name << parent_channel.Name() << ".RType";
  if (IChannel* type = CreateBitsChannel(parent_channel, name.str(),
                    byte_offset,4, 4);
      type != nullptr ) {
    type->Flags(CnFlag::BusEvent);
    if (IChannelConversion* cc_type = type->CreateChannelConversion();
        cc_type != nullptr) {
      cc_type->Type(ConversionType::ValueToText);
      cc_type->Name("Most25MessageType");
      cc_type->Parameter(0, 0x00);
      cc_type->Parameter(1, 0x01);
      cc_type->Parameter(2, 0x02);
      cc_type->Parameter(3, 0x03);
      cc_type->Parameter(4, 0x04);
      cc_type->Parameter(5, 0x05);
      cc_type->Reference(0, "Normal Message");
      cc_type->Reference(1, "Remote Read Message");
      cc_type->Reference(2, "Remote Write Message");
      cc_type->Reference(3, "Remote Resource Allocate Message");
      cc_type->Reference(4, "Remote Resource Deallocate Message");
      cc_type->Reference(5, "Remote Get Source Message");
      cc_type->Reference(6, "Unknown Message");  // Default text

      CcComment cc_comment("MOST25 message types");
      cc_type->SetCcComment(cc_comment);
    }
  }

}
}  // namespace mdf