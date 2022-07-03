#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <bitset>
#include <string>
#include <pybind11/pybind11.h>
#include "sha256/sha256/sha256.h"

namespace py = pybind11;

#include "bip39.h"
#include "utils.h"

std::vector<int> POSSIBLE_WORD_COUNT = {12, 15, 18, 21, 24};


std::string Bip39::generate_entropy() {
	std::string random_bytes_hex = generate_random_bytes(this->entropy_length / 8);
	this->entropy_ = random_bytes_hex;
	return random_bytes_hex;
}


std::string Bip39::generate_checksum(std::string& entropy_string) const {
	std::string result;

	std::string entropy_sha256 = sha256(hex_str_to_bin_str(entropy_string));
	std::string sha256_bin = hex_str_to_bin_str(entropy_sha256);

	// take checksum bits of the sha526 string
	std::string result_to_append = sha256_bin.substr(0, this->checksum);

	// append it to the initial entropy
	result = entropy_string + result_to_append;

	return result;
}


std::string Bip39::generate_mnemonic(std::string& checksum_string) const {
	std::vector<std::string> v;
	auto words_dict = get_words(this->langage_);

	for (int i = 0; i < checksum_string.length(); i += 11) {
		auto sub = checksum_string.substr(i, 11);
		auto word = words_dict[std::stoi(sub, nullptr, 2)];
		v.push_back(word);
	}

	std::string result = std::accumulate(std::next(begin(v)), end(v), v[0],
				[](std::string a, std::string b) {
					return std::move(a) + " " + b;
				});

	return result;
}


std::string Bip39::generate(int word_count) {
	if (std::find(begin(POSSIBLE_WORD_COUNT), end(POSSIBLE_WORD_COUNT), word_count) == end(POSSIBLE_WORD_COUNT)) {
		throw std::invalid_argument("The number of words wanted must be in [12, 15, 18, 21, 24] interval");
	}
	this->word_count = word_count;
	this->checksum = (this->word_count * 11) % 32;
	this->entropy_length = (this->word_count * 11) - this->checksum;

	auto entropy_string = this->generate_entropy();
	entropy_string = hex_str_to_bin_str(entropy_string);
	auto checksum_string = this->generate_checksum(entropy_string);
	this->mnemonic_  = this->generate_mnemonic(checksum_string);
	return this->mnemonic_;
}


std::string Bip39::generate_given_entropy(std::string entropy) {

	this->entropy_length = entropy.length() * 4;
	this->checksum = this->entropy_length / 32;
	this->word_count = (this->entropy_length + this->checksum) / 11;
	this->entropy_ = entropy;
	if (std::find(begin(POSSIBLE_WORD_COUNT), end(POSSIBLE_WORD_COUNT), this->word_count) == end(POSSIBLE_WORD_COUNT)) {
                throw std::invalid_argument("The entropy given doesn't have a word count in [12, 15, 18, 21, 24] interval");
        }

	auto entropy_string = hex_str_to_bin_str(entropy);
	auto checksum_string = this->generate_checksum(entropy_string);
	this->mnemonic_ = this->generate_mnemonic(checksum_string);
	return this->mnemonic_;
}


std::string Bip39::retrieve_entropy(std::string mnemonic_sentence) {
	std::stringstream ss(mnemonic_sentence);
	std::string buf;
	std::vector<std::string> words;
    	while (ss >> buf) {
        	words.push_back(buf);
	}
	auto words_dict = get_words(this->langage_);
	std::string words_string_binary;
	this->word_count = words.size();

	std::for_each(words.begin(), words.end(),
		[&](std::string const& w){
			auto it = std::find(words_dict.begin(), words_dict.end(), w);
			if (it == words_dict.end()) {
				throw std::invalid_argument("The word : " + w + "is not in the wordlist!");
			}
			words_string_binary += std::bitset<11>(it - words_dict.begin()).to_string();
		});

	std::string words_without_checksum = words_string_binary.substr(0, words_string_binary.length() - this->word_count);
	std::string result;

	for (auto i = 0; i < words_without_checksum.length(); i += 8){
        	result += bin_str_to_hex_str(words_without_checksum.substr(i, 8));
    	}
	this->entropy_ = result;
	return this->entropy_;
}


bool Bip39::verify_mnemonic(std::string& entropy_string, std::string& mnemonic_sentence) {

	// TODO verify right arguments

	int checksum = entropy_string.length() * 4 / 32;
	int word_count = (checksum + entropy_string.length() * 4) / 11;

	// first check

	this->word_count = word_count;
        this->checksum = checksum;
        this->entropy_length = entropy_string.length() * 4;

	entropy_string = hex_str_to_bin_str(entropy_string);
        auto checksum_string = this->generate_checksum(entropy_string);
        auto expected_mnemonic_sentence  = this->generate_mnemonic(checksum_string);
	return expected_mnemonic_sentence.compare(mnemonic_sentence) == 0;
}


PYBIND11_MODULE(bip39, comp) {
    py::class_<Bip39>(comp, "Bip39")
        .def(py::init<const std::string &>(), py::arg("langage") = "en")
	.def("get_langage", &Bip39::get_langage)
	.def("set_langage", &Bip39::set_langage)
	.def("get_mnemonic", &Bip39::get_mnemonic)
	.def("get_entropy", &Bip39::get_entropy)
        .def("generate", &Bip39::generate)
	.def("generate_given_entropy", &Bip39::generate_given_entropy)
	.def("retrieve_entropy", &Bip39::retrieve_entropy)
	.def("verify_mnemonic", &Bip39::verify_mnemonic);
}

