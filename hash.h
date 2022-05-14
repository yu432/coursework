extern unsigned int seed_for_hash_1;
extern unsigned int seed_for_hash_2;
extern unsigned int seed_for_hash_3;

extern unsigned int start_num_1;
extern unsigned int start_num_2;
extern unsigned int start_num_3;


unsigned int MurmurHash_1(const char *key, unsigned int len) {
  const unsigned int m = start_num_1;
  const unsigned int seed = seed_for_hash_1;
  const int r = 24;
  unsigned int h = seed ^ len;
  const auto *data = (const unsigned char *)key;
  unsigned int k;
  while (len >= 4) {
    k = data[0];
    k |= data[1] << 8;
    k |= data[2] << 16;
    k |= data[3] << 24;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  switch (len) {
  case 3:
    h ^= data[2] << 16;
  case 2:
    h ^= data[1] << 8;
  case 1:
    h ^= data[0];
    h *= m;
  }

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

unsigned int MurmurHash_2(const char *key, unsigned int len) {
  const unsigned int m = start_num_2;
  const unsigned int seed = seed_for_hash_2;
  const int r = 24;
  unsigned int h = seed ^ len;
  const auto *data = (const unsigned char *)key;
  unsigned int k;
  while (len >= 4) {
    k = data[0];
    k |= data[1] << 8;
    k |= data[2] << 16;
    k |= data[3] << 24;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  switch (len) {
  case 3:
    h ^= data[2] << 16;
  case 2:
    h ^= data[1] << 8;
  case 1:
    h ^= data[0];
    h *= m;
  }

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

unsigned int MurmurHash_3(const char *key, unsigned int len) {
  const unsigned int m = start_num_3;
  const unsigned int seed = seed_for_hash_3;
  const int r = 24;
  unsigned int h = seed ^ len;
  const auto *data = (const unsigned char *)key;
  unsigned int k;
  while (len >= 4) {
    k = data[0];
    k |= data[1] << 8;
    k |= data[2] << 16;
    k |= data[3] << 24;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  switch (len) {
  case 3:
    h ^= data[2] << 16;
  case 2:
    h ^= data[1] << 8;
  case 1:
    h ^= data[0];
    h *= m;
  }

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

unsigned int FNVHash(const char *pBuffer, unsigned int len) {
  const uint64_t MagicPrime = 0x00000100000001b3;
  uint64_t Hash = 0xcbf29ce484222325;
  for (size_t i = 0; i < len; i++) {
    Hash = (Hash ^ pBuffer[i]) * MagicPrime;
  }
  return Hash;
}

unsigned int JenkinsHash(const char *key, size_t len) {
  unsigned int hash, i;
  for (hash = i = 0; i < len; ++i) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}