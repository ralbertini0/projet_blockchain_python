from PKDF2_HMAC512 import PKDF2_HMAC512
import bip39 as bp



# gen = bp.Bip39("en")
# seed = gen.generate(12)
seed = "random"

def test_hash_stable():
    test_PKDF2_HMAC512 = PKDF2_HMAC512("projet_password",seed)
    hash1 = test_PKDF2_HMAC512.get_hash()
    hash2 = test_PKDF2_HMAC512.get_hash()
    assert hash1 == hash2

def test_hash_unicity():
    test1_PKDF2_HMAC512 = PKDF2_HMAC512("projet_password1",seed)
    test2_PKDF2_HMAC512 = PKDF2_HMAC512("projet_password2",seed)
    hash1 = test1_PKDF2_HMAC512.get_hash()
    hash2 = test2_PKDF2_HMAC512.get_hash()
    assert hash1 != hash2

try:
    test_hash_stable()
    test_hash_unicity()
    print("Test OK")
except:
    print("Test KO")
