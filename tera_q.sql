-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Aug 14, 2016 at 08:51 PM
-- Server version: 10.1.13-MariaDB
-- PHP Version: 5.6.23

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `tera_q`
--

-- --------------------------------------------------------

--
-- Table structure for table `accounts`
--

CREATE TABLE `accounts` (
  `id` int(64) NOT NULL,
  `username` varchar(32) NOT NULL,
  `password` varchar(64) NOT NULL,
  `email` varchar(64) NOT NULL,
  `lastOnlineUTC` int(64) NOT NULL,
  `coins` int(11) NOT NULL,
  `isGm` tinyint(1) NOT NULL,
  `ramainingPlayTime` int(64) NOT NULL,
  `hardwareInfo` text NOT NULL,
  `accountSettings` blob NOT NULL,
  `accountSettingsSize` int(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `accounts`
--

INSERT INTO `accounts` (`id`, `username`, `password`, `email`, `lastOnlineUTC`, `coins`, `isGm`, `ramainingPlayTime`, `hardwareInfo`, `accountSettings`, `accountSettingsSize`) VALUES
(3, 'admin', 'admin', 'admin@mail.com', 1469971359, 0, 1, 0, '0', '', 0);

-- --------------------------------------------------------

--
-- Table structure for table `players`
--

CREATE TABLE `players` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `x` double NOT NULL,
  `y` double NOT NULL,
  `z` double NOT NULL,
  `h` int(16) NOT NULL,
  `race` int(11) NOT NULL,
  `gender` int(11) NOT NULL,
  `class` int(11) NOT NULL,
  `exp` int(11) NOT NULL,
  `restedExp` int(11) NOT NULL,
  `areaId` int(11) NOT NULL,
  `level` int(11) NOT NULL,
  `details1` mediumblob,
  `details2` mediumblob,
  `headData` tinyblob,
  `lastOnlineUTC` int(64) NOT NULL,
  `creationTimeUTC` int(64) NOT NULL,
  `banTimeUTC` int(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `players`
--

INSERT INTO `players` (`username`, `name`, `x`, `y`, `z`, `h`, `race`, `gender`, `class`, `exp`, `restedExp`, `areaId`, `level`, `details1`, `details2`, `headData`, `lastOnlineUTC`, `creationTimeUTC`, `banTimeUTC`) VALUES
('admin', 'Glass', -818.11969, 8820.540039, 2172.840088, 64794, 2, 0, 0, 1, 0, 1, 65, 0x100e101030303030101212301809043005301010300d12301008051316101205, 0x0113101313101313130f0f0f0f0f0f0f101330303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030, 0x650d09010b303001, 1470949148, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `player_deposit`
--

CREATE TABLE `player_deposit` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `items` blob NOT NULL,
  `itemsCount` int(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `player_inventory`
--

CREATE TABLE `player_inventory` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `items` blob,
  `itemsCount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `player_skills`
--

CREATE TABLE `player_skills` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `learnedSkills` mediumblob NOT NULL,
  `skillCount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `player_skills`
--

INSERT INTO `player_skills` (`username`, `name`, `learnedSkills`, `skillCount`) VALUES
('admin', 'Glass', 0x01000000, 1);

-- --------------------------------------------------------

--
-- Table structure for table `player_skin_warehouse`
--

CREATE TABLE `player_skin_warehouse` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `headSkin` int(32) NOT NULL,
  `faceSkin` int(32) NOT NULL,
  `bodySkin` int(32) NOT NULL,
  `weaponSkin` int(32) NOT NULL,
  `backSkin` int(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `player_skin_warehouse`
--

INSERT INTO `player_skin_warehouse` (`username`, `name`, `headSkin`, `faceSkin`, `bodySkin`, `weaponSkin`, `backSkin`) VALUES
('admin', 'Glass', 0, 0, 180702, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `player_warehouse`
--

CREATE TABLE `player_warehouse` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `weapon` int(32) NOT NULL,
  `chest` int(32) NOT NULL,
  `gloves` int(32) NOT NULL,
  `boots` int(32) NOT NULL,
  `ring1` int(32) NOT NULL,
  `ring2` int(32) NOT NULL,
  `earring1` int(32) NOT NULL,
  `earring2` int(32) NOT NULL,
  `necklace` int(32) NOT NULL,
  `innerware` int(32) NOT NULL,
  `broch` int(32) NOT NULL,
  `belt` int(32) NOT NULL,
  `skin1` int(32) NOT NULL,
  `skin2` int(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `player_warehouse`
--

INSERT INTO `player_warehouse` (`username`, `name`, `weapon`, `chest`, `gloves`, `boots`, `ring1`, `ring2`, `earring1`, `earring2`, `necklace`, `innerware`, `broch`, `belt`, `skin1`, `skin2`) VALUES
('admin', 'Glass', 96726, 88081, 97256, 96608, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `test`
--

CREATE TABLE `test` (
  `a` int(11) NOT NULL,
  `data` tinyblob NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `test`
--

INSERT INTO `test` (`a`, `data`) VALUES
(1, 0x0102030405060708090a),
(2, 0x0102030405060708090a),
(32, 0x0102030405060708090a),
(10, 0x30010203040506070809);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `id_2` (`id`),
  ADD UNIQUE KEY `username` (`username`),
  ADD KEY `id` (`id`);

--
-- Indexes for table `players`
--
ALTER TABLE `players`
  ADD PRIMARY KEY (`name`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `player_inventory`
--
ALTER TABLE `player_inventory`
  ADD PRIMARY KEY (`name`);

--
-- Indexes for table `player_skills`
--
ALTER TABLE `player_skills`
  ADD PRIMARY KEY (`name`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `player_skin_warehouse`
--
ALTER TABLE `player_skin_warehouse`
  ADD PRIMARY KEY (`name`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `player_warehouse`
--
ALTER TABLE `player_warehouse`
  ADD PRIMARY KEY (`name`),
  ADD UNIQUE KEY `name` (`name`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `accounts`
--
ALTER TABLE `accounts`
  MODIFY `id` int(64) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
