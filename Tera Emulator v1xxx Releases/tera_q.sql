-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Sep 07, 2016 at 03:45 PM
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
  `accountSettings` blob,
  `accountSettingsSize` int(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `accounts`
--

INSERT INTO `accounts` (`id`, `username`, `password`, `email`, `lastOnlineUTC`, `coins`, `isGm`, `ramainingPlayTime`, `hardwareInfo`, `accountSettings`, `accountSettingsSize`) VALUES
(6, 'admin', '21232f297a57a5a743894a0e4a801fc3', 'admin@mail.com', 0, 0, 1, 0, '', 0x0830700f08975612043223435052886e089756522053303130433068306130743043306f306e30743072306f306c306c3065307230a201d87478dad558c16b45189f2fdb5d64101916918784323ed318636d9bcd66135ea1cd66779b2ed9dd3c76b7d6e0218804fa61f454a8c483a0a2281e046f928ba03745a12054b0680f627bd043a4825ebc597a11050f71e6db7d99b77933efcd6c538b7424fbdefbfdbef9bef9be6fbedfbe47fedc2abeff68483e02720ff6a21ff87a427d7e2ff773fed7dc1df8ecc863cbe4157289bc4c2e9380cc9177f284fcbe723bfffcdf79d82ec05b85a335729e54495ffc6e909034c826e99075d2256d71b745766ec783d924a44aea02d014d001bc2f3ed7c4939d020f322d1e722693905077f1dab0a4021c526b6f95108096f03305202d4ac064f06412d0177fabc2e99d821ff0e4e38be24e93f4f0aa6bb2d115d74d0836983133393536de148e36705361b632c0a3e12f0595f4ddeaa1ed2e9128b9521353d717d499603a49952e7431619b98e173e2b3017a11612d742a031a772803aa5217874e6153e61cc581da44a8c7e5a0a47fdcc7c8ab629be4deae636d2b9aa10664501d84ad6ed089e0b82e9c86b8dac42d6fa0af5da4c9dc9582533604591df26e614b49eb4a446a9017c51dc37645a03686d7c066f38209b5169a7ab9b835e1dba097b5bed4312badfd6dd1f65f8fac61965b266743e14593bc8077e5f59c2db0640b9cb705966d810bb6c08a2d70d116b8448ad742701f6ea5f8502038140cf5d51976c81863411b421bcbba2aaece0f0b32a5b8e38b6b412bd855ab784a76ccbda5ce96108fb9f6d04fe940f1562e9c70dfc1f9e4581d67c29977efb0a6c374fdd0c65ac64cb61c61c5d77361ce3da3e5644f64688cc3c868dc9ec364d4daba8063691d3b416b4b011a7854f7d12f6d186e6a5548717828fef7c4b3e236728fb8e7612199874c7969386a36301ff29e1cf16b26e13430d6f0701dc429ad1ea45682b2897a0e74d1f093c3b08aaead9a61fe801861caf1d81e1ada29d483157b47cd66523666d449a78d1933bed6f0b46edc5f7c71338e2d98a113ef57f03ac8e8ff4e1b, 0);

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
  `banTimeUTC` int(64) NOT NULL,
  `visitedSections` mediumblob,
  `worldMapGuardId` int(11) NOT NULL,
  `worldMapWorldId` int(11) NOT NULL,
  `worldMapSectionId` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `player_bank`
--

CREATE TABLE `player_bank` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `items` blob NOT NULL,
  `slotCount` int(11) NOT NULL,
  `gold` bigint(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `player_inventory`
--

CREATE TABLE `player_inventory` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `items` blob,
  `slotCount` int(11) NOT NULL,
  `gold` bigint(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `player_settings`
--

CREATE TABLE `player_settings` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `settings` mediumblob
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `player_skills`
--

CREATE TABLE `player_skills` (
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `learnedSkills` mediumblob,
  `skillCount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

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
-- Indexes for table `player_bank`
--
ALTER TABLE `player_bank`
  ADD PRIMARY KEY (`name`);

--
-- Indexes for table `player_inventory`
--
ALTER TABLE `player_inventory`
  ADD PRIMARY KEY (`name`);

--
-- Indexes for table `player_settings`
--
ALTER TABLE `player_settings`
  ADD PRIMARY KEY (`name`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `player_skills`
--
ALTER TABLE `player_skills`
  ADD PRIMARY KEY (`name`),
  ADD UNIQUE KEY `name` (`name`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `accounts`
--
ALTER TABLE `accounts`
  MODIFY `id` int(64) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
