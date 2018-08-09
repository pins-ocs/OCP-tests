function m = cellvec2mat(cv)
  nc = length(cv);
  nr = length(cv{1});
  m = zeros(nr,nc);
  for i=1:nc
    m(:,i) = cv{i};
  end
end