#ifndef GRAVY_RFC2898DERIVEBYTES_HPP
#define GRAVY_RFC2898DERIVEBYTES_HPP

#include <vector>
#include <cstdint>

typedef struct {
    unsigned long total[2];	/*!< number of bytes processed  */
    unsigned long state[8];	/*!< intermediate digest state  */
    unsigned char buffer[64];	/*!< data block being processed */

    unsigned char ipad[64];	/*!< HMAC: inner padding        */
    unsigned char opad[64];	/*!< HMAC: outer padding        */
    int is224;		/*!< 0 => SHA-256, else SHA-224 */
} sha2_context;

namespace Gravy::System::Security::Cryptography
{
    class Rfc2898DeriveBytes
    {
    private:
        sha2_context context;
    public:
        Rfc2898DeriveBytes();
        std::vector<uint8_t> Pbkdf2(uint8_t *password, size_t passwordLength, uint8_t *salt, size_t saltLength, size_t iterations, size_t keyLength);
        void Reset();
    };
};

#endif