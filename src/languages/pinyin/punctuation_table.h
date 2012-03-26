// Copyright 2010-2012, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_LANGUAGES_PINYIN_PUNCTUATION_TABLE_H_
#define MOZC_LANGUAGES_PINYIN_PUNCTUATION_TABLE_H_

#include <map>
#include <string>
#include <vector>

#include "base/port.h"
#include "base/singleton.h"

namespace mozc {
namespace pinyin {
namespace punctuation {

class PunctuationTableInterface {
 public:
  virtual ~PunctuationTableInterface() {}

  // All candidates contain only one character.
  virtual bool GetCandidates(char key, vector<string> *candidates) const = 0;
  virtual void GetDefaultCandidates(vector<string> *candidates) const = 0;

  // Commit text may contain multi characters.
  virtual bool GetDirectCommitTextForSimplifiedChinese(
      char key, string *commit_text) const = 0;
  // Commit text may contain multi characters.
  virtual bool GetDirectCommitTextForTraditionalChinese(
      char key, string *commit_text) const = 0;
};

class PunctuationTable : public PunctuationTableInterface {
 public:
  virtual ~PunctuationTable();
  bool GetCandidates(char key, vector<string> *candidates) const;
  void GetDefaultCandidates(vector<string> *candidates) const;

  bool GetDirectCommitTextForSimplifiedChinese(
      char key, string *commit_text) const;
  bool GetDirectCommitTextForTraditionalChinese(
      char key, string *commit_text) const;

 private:
  friend class Singleton<PunctuationTable>;

  bool GetDirectCommitTextInternal(char key, string *commit_text) const;

  vector<string> default_candidates_;
  map<char, vector<string> > conversion_map_;
  map<char, string> commit_map_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(PunctuationTable);
};

}  // namespace punctuation
}  // namespace pinyin
}  // namespace mozc

#endif  // MOZC_LANGUAGES_PINYIN_PUNCTUATION_TABLE_H_