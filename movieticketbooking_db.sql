-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 06, 2024 at 10:13 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `movieticketbooking_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `customer_tb`
--

CREATE TABLE `customer_tb` (
  `id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL DEFAULT '0',
  `phone` varchar(50) NOT NULL DEFAULT '0',
  `movie` varchar(50) NOT NULL DEFAULT '0',
  `format` varchar(50) NOT NULL DEFAULT '0',
  `seat` int(11) NOT NULL DEFAULT 0,
  `price` float NOT NULL DEFAULT 0,
  `showdate` varchar(50) NOT NULL DEFAULT '0',
  `showtime` varchar(50) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `customer_tb`
--

INSERT INTO `customer_tb` (`id`, `name`, `phone`, `movie`, `format`, `seat`, `price`, `showdate`, `showtime`) VALUES
(1, 'Saifur', '01793385050', 'Toofan', '2d', 2, 740, '2024-08-07', '9:30'),
(2, 'Toufika', '0123456789', 'Drishyam', '2d', 2, 800, '2024-08-10', '3:20');

-- --------------------------------------------------------

--
-- Table structure for table `movie_tb`
--

CREATE TABLE `movie_tb` (
  `m_id` int(11) NOT NULL,
  `m_name` varchar(50) NOT NULL DEFAULT '0',
  `m_genre` varchar(50) NOT NULL DEFAULT '0',
  `m_format` varchar(50) NOT NULL,
  `m_showdate` varchar(50) NOT NULL,
  `m_showtime` varchar(50) NOT NULL,
  `m_ticketprice` float NOT NULL,
  `m_seat` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `movie_tb`
--

INSERT INTO `movie_tb` (`m_id`, `m_name`, `m_genre`, `m_format`, `m_showdate`, `m_showtime`, `m_ticketprice`, `m_seat`) VALUES
(1, 'Toofan', 'Action', '2d', '2024-08-07', '9:30', 370, 54),
(2, 'Drishyam', 'Thriller', '2d', '2024-08-10', '3:20', 400, 47);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `customer_tb`
--
ALTER TABLE `customer_tb`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `movie_tb`
--
ALTER TABLE `movie_tb`
  ADD PRIMARY KEY (`m_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `customer_tb`
--
ALTER TABLE `customer_tb`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `movie_tb`
--
ALTER TABLE `movie_tb`
  MODIFY `m_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
