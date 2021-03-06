#include <libral/type.hpp>

#include <map>
#include <memory>
#include <boost/nowide/iostream.hpp>

#include <typeinfo>

namespace libral {

  boost::optional<std::unique_ptr<resource>>
  type::find(const std::string &name) {
    return _prov->find(name);
  }

  std::vector<std::unique_ptr<resource>> type::instances(void) {
    auto result = _prov->instances();
    _prov->flush();

    return result;
  }

  std::pair<std::unique_ptr<resource>, result<changes>>
  type::update(const std::string& name,
               const attr_map& attrs) {
    auto opt_rsrc = _prov->find(name);
    std::unique_ptr<resource> res;

    if (opt_rsrc) {
      res = std::move(*opt_rsrc);
    } else {
      res = _prov->create(name);
    }
    auto ch = res->update(attrs);
    return
      std::pair<std::unique_ptr<resource>,
                result<changes>>(std::move(res),
                                 std::move(ch));
  }

  result<value> type::parse(const std::string &name, const std::string &v) {
    return _prov->parse(name, v);
  }

}
