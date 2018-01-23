var questionInfo = [
 { id:  1, location: [90, 90, 30], genre: "Carnatic", clues: [{slideid: 1}],
	answer: {slideid: 2}},
 { id:  2, location: [90, 80, 30], genre: "Hindustani", clues: [{slideid: 3}],
	answer: {slideid: 4}},
 { id:  3, location: [60, 70, 30], genre: "Caribbean", clues: [{slideid: 5},{slideid: 6, vid: 1}],
	answer: {slideid: 7}},
 { id:  4, location: [70, 80, 30], genre: "Ghazal", clues: [{slideid: 8}],
	answer: {slideid: 9}},
 { id:  5, location: [60, 50, 30], genre: "Algerian", clues: [{slideid: 10},{slideid: 11, vid: 2}],
	answer: {slideid: 12}},
 { id:  6, location: [90, 30, 30], genre: "Thai Pop", clues: [{slideid: 13}],
	answer: {slideid: 14}},
 { id:  7, location: [80, 60, 30], genre: "Bolly\nwood 1", clues: [{slideid: 15}],
	answer: {slideid: 16}},
 { id:  8, location: [80, 50, 30], genre: "Bolly\nwood 2", clues: [{slideid: 17}], 
	answer: {slideid: 18}},
 { id:  9, location: [80, 40, 30], genre: "Indipop\n1", clues: [{slideid: 19, vid: 3},{slideid: 20},{slideid: 21, vid : 4}],
	answer: {slideid: 22}},
 { id: 10, location: [80, 30, 30], genre: "Indipop\n2", clues: [{slideid: 23},{slideid: 24, vid : 5}],
	answer: {slideid: 25}},
 { id: 11, location: [90, 20, 30], genre: "Korean", clues: [{slideid: 26},{slideid: 27}],
	answer: {slideid: 28}},
 { id: 12, location: [10, 60, 30], genre: "60s\nPop", clues: [{slideid: 29}, {slideid: 30, vid : 6}],
	answer: {slideid: 31}},
 { id: 13, location: [20, 70, 30], genre: "Jazz", clues: [{slideid: 32}],
	answer: {slideid: 33}},
 { id: 14, location: [20, 60, 30], genre: "Soul", clues: [{slideid: 34}],
	answer: {slideid: 35}},
// 36, 37 - dumped
 { id: 15, location: [30, 90, 35], genre: "Western\nClassical", clues: [{slideid: 38}],
	answer: {slideid: 39}},
 { id: 16, location: [50, 80, 35], genre: "Rip Offs(AP)", clues: [{slideid: 40, vid: 8}],
	answer: {slideid: 41}},
 { id: 17, location: [10, 50, 35], genre: "Local\nVariables(AP)", clues: [{slideid: 42},{slideid: 43},{slideid: 44},{slideid: 45},{slideid: 46},{slideid: 47}],
	answer: {slideid: 48}},
 { id: 18, location: [30, 40, 35], genre: "UnVidia\n(AP)", clues: [{slideid: 49},{slideid: 50},{slideid: 51},{slideid: 52},{slideid: 53},{slideid: 54},{slideid: 55}],
	answer: {slideid: 56}},
 { id: 19, location: [40, 60, 35], genre: "TV Tunes\n(AP)", clues: [{slideid: 57, vid: 9}],
	answer: {slideid: 58}},
 { id: 20, location: [30, 20, 35], genre: "N || K\n(AP)", clues: [{slideid: 59},{slideid: 60, vid: 10}],
	answer: {slideid: 61}},
 { id: 21, location: [30, 60, 35], genre: "In Living\nCover (AP)", clues: [{slideid: 62},{slideid: 63, vid: 11}],
	answer: {slideid: 64}},
 { id: 22, location: [10, 30, 30], genre: "Heavy\nMetal", clues: [{slideid: 65}],
	answer: {slideid: 66}},
 { id: 23, location: [10, 20, 30], genre: "Death\nMetal", clues: [{slideid: 67},{slideid: 68}],
	answer: {slideid: 69}},
 { id: 24, location: [20, 30, 30], genre: "90's R & B", clues: [{slideid: 70}],
	answer: {slideid: 71}},
 { id: 25, location: [20, 20, 30], genre: "00's R & B", clues: [{slideid: 72}],
	answer: {slideid: 73}},
 { id: 26, location: [30, 50, 30], genre: "70's Disco", clues: [{slideid: 74}],
	answer: {slideid: 75}},
 { id: 27, location: [20, 50, 30], genre: "80's Disco", clues: [{slideid: 76},{slideid: 77, vid: 12}],
	answer: {slideid: 78}},
 { id: 28, location: [40, 40, 30], genre: "Synth", clues: [{slideid: 79},{slideid: 80, vid: 13}],
	answer: {slideid: 81}},
 { id: 29, location: [20, 10, 30], genre: "Neo Soul", clues: [{slideid: 82},{slideid: 83, vid: 14}],
	answer: {slideid: 84}},
 { id: 30, location: [30, 30, 30], genre: "80's Pop", clues: [{slideid: 85}],
	answer: {slideid: 86}},
 { id: 31, location: [30, 10, 30], genre: "90's Pop", clues: [{slideid: 87}],
	answer: {slideid: 88}},
 { id: 32, location: [20, 40, 30], genre: "Rock", clues: [{slideid: 89}],
	answer: {slideid: 90}},
 { id: 33, location: [10, 10, 30], genre: "Emo", clues: [{slideid: 91}],
	answer: {slideid: 92}},
 { id: 34, location: [40, 50, 30], genre: "Reggae", clues: [{slideid: 93}],
	answer: {slideid: 94}},
 { id: 35, location: [50, 60, 30], genre: "Country", clues: [{slideid: 95}],
	answer: {slideid: 96}},
 { id: 36, location: [40, 20, 30], genre: "Hip Hop", clues: [{slideid: 97}],
	answer: {slideid: 98}},
 { id: 37, location: [40, 30, 30], genre: "Folk", clues: [{slideid: 99}],
	answer: {slideid: 100}},
];