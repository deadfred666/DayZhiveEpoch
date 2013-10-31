SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `Default_LOADOUT`
-- ----------------------------

CREATE TABLE `Default_LOADOUT` (
  `InstanceID` bigint(20) unsigned NOT NULL,
  `Inventory` varchar(2048) NOT NULL DEFAULT '[]',
  `Backpack` varchar(2048) NOT NULL DEFAULT '["DZ_Patrol_Pack_EP1",[[],[]],[[],[]]]',
  PRIMARY KEY (`InstanceID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;