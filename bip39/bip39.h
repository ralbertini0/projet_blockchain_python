#include <string>

class Bip39 {

	std::string mnemonic_;
	std::string langage_;
	std::string entropy_;

	int checksum;
	int word_count;
	int entropy_length;

	/**
	 * @brief Generate the initial random entropy
	 * @return String of the entropy converted to a binary buffer.
	 */
	std::string generate_entropy();

	/**
         * @brief Generate the checksum string and append it to the initial entropy
         * @param entropy_string Entropy
	 * @return String of the entropy with the checksum added.
         */
	std::string generate_checksum(std::string& entropy_string) const;
	
	/**
         * @brief Generate the mnemonic sentence
	 * @checksum_string Entropy with checksum
         * @return String of the mnemonic sentence.
         */
	std::string generate_mnemonic(std::string& checksum_string) const;

public:
	Bip39(std::string langage = "en") : langage_(langage) {};
	~Bip39() = default;

	/**
         * @brief Main function for generate a mnemonic sentence
	 * @param word_count Number of words, must be in [12, 15, 18, 21, 24]
         * @return String of the mnemonic sentence in the langage selected, by default "en";
         */
	std::string generate(int word_count);

	/**
	 * @brief Generate mnemonic sentence given an entropy
         * @param entropy string of the entropy
         * @return String of the mnemonic sentence in the langage selected, by default "en";
	 */
	std::string generate_given_entropy(std::string entropy);

	/**
	 * @brief Retrieve Entropy given a mnemonic sentence
         * @param mnemonic_sentence string of the mnemonic sentence
         * @return String of the entropy
	 */
	std::string retrieve_entropy(std::string mnemonic_sentence);


	/**
	 * @brief Verify the mnemonic sentence given the entropy.
	 * @param entropy_string Entropy
	 * @param mnemonic_sentence Mnemonic sentence
	 * @return Boolean whether the given entropy gives the same mnemonic sentence
	 */
	bool verify_mnemonic(std::string& entropy_string, std::string& mnemonic_sentence);

	// Getters setters
	std::string get_langage() const { return this->langage_; };
	void set_langage(std::string langage) { this->langage_ = langage; };
	std::string get_mnemonic() const { return this->mnemonic_; };
	std::string get_entropy() const {return this->entropy_; };
};
