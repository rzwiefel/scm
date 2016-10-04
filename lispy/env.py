class Env(dict):
    def __init__(self, params=None, outer=None, **kwargs):
        self.update({} if params is None else params)
        self.outer = outer

    def find(self, var):
        if var in self:
            return self
        elif self.outer is not None:
            return self.outer.find(var)
        else:
            return None

    def __get_innerds(self):
        innerds = [i for i in self]
        innerds = filter(lambda x: not x.startswith('_'), innerds)
        res = {i: self.get(i) for i in innerds}
        return res

    def env(self):
        if self.outer is None:
            return self.__get_innerds()
        else:
            return self.__get_innerds() + self.outer.env()
